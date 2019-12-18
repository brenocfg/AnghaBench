#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* sys; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_tls_server_t ;
struct TYPE_11__ {int /*<<< orphan*/ * whitelist; int /*<<< orphan*/ * server_cert_chain; } ;
typedef  TYPE_2__ vlc_tls_creds_sys_t ;
struct TYPE_13__ {void* member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int member_0; TYPE_4__* member_1; } ;
typedef  int /*<<< orphan*/  SecTrustResultType ;
typedef  int /*<<< orphan*/ * SecTrustRef ;
typedef  int /*<<< orphan*/ * SecPolicyRef ;
typedef  int /*<<< orphan*/ * SecKeychainSearchRef ;
typedef  int /*<<< orphan*/ * SecKeychainItemRef ;
typedef  TYPE_3__ SecKeychainAttributeList ;
typedef  TYPE_4__ SecKeychainAttribute ;
typedef  int /*<<< orphan*/ * SecIdentityRef ;
typedef  int /*<<< orphan*/ * SecCertificateRef ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  CSSM_TP_APPLE_EVIDENCE_INFO ;
typedef  int /*<<< orphan*/ * CFMutableArrayRef ;
typedef  int CFIndex ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayAppendArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayAppendValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFArrayCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int CFArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRangeMake (int,int) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIdentityCreateWithCertificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SecKeychainSearchCopyNext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SecKeychainSearchCreateFromAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * SecPolicyCreateSSL (int,int /*<<< orphan*/ *) ; 
 scalar_t__ SecTrustCreateWithCertificates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SecTrustEvaluate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SecTrustGetResult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFTypeArrayCallBacks ; 
 int /*<<< orphan*/  kSecCertificateItemClass ; 
 int /*<<< orphan*/  kSecLabelItemAttr ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  st_ServerOps ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int OpenServer (vlc_tls_server_t *crd, const char *cert, const char *key) {

    /*
     * This function expects the label of the certificate in "cert", stored
     * in the MacOS keychain. The appropriate private key is found automatically.
     */
    VLC_UNUSED(key);
    OSStatus ret;

    msg_Dbg(crd, "open st server");

    /*
     * Get the server certificate.
     *
     * This API is deprecated, but the replacement SecItemCopyMatching
     * only works on >= 10.7
     */
    SecKeychainAttribute attrib = { kSecLabelItemAttr, strlen(cert), (void *)cert };
    SecKeychainAttributeList attrList = { 1, &attrib };

    SecKeychainSearchRef searchReference = NULL;
    ret = SecKeychainSearchCreateFromAttributes(NULL, kSecCertificateItemClass,
                                                 &attrList, &searchReference);
    if (ret != noErr || searchReference == NULL) {
        msg_Err(crd, "Cannot find certificate with alias %s", cert);
        return VLC_EGENERIC;
    }

    SecKeychainItemRef itemRef = NULL;
    ret = SecKeychainSearchCopyNext(searchReference, &itemRef);
    if (ret != noErr) {
        msg_Err(crd, "Cannot get certificate with alias %s, error: %d", cert, ret);
        return VLC_EGENERIC;
    }
    CFRelease(searchReference);

    /* cast allowed according to documentation */
    SecCertificateRef certificate = (SecCertificateRef)itemRef;

    SecIdentityRef cert_identity = NULL;
    ret = SecIdentityCreateWithCertificate(NULL, certificate, &cert_identity);
    if (ret != noErr) {
        msg_Err(crd, "Cannot get private key for certificate");
        CFRelease(certificate);
        return VLC_EGENERIC;
    }

    /*
     * We try to validate the server certificate, but do not care about the result.
     * The only aim is to get the certificate chain.
     */
    SecPolicyRef policy = SecPolicyCreateSSL(true, NULL);
    SecTrustRef trust_ref = NULL;
    int result = VLC_SUCCESS;

    /* According to docu its fine to pass just one certificate */
    ret = SecTrustCreateWithCertificates((CFArrayRef)certificate, policy, &trust_ref);
    if (ret != noErr) {
        msg_Err(crd, "Cannot create trust");
        result = VLC_EGENERIC;
        goto out;
    }

    SecTrustResultType status;
    ret = SecTrustEvaluate(trust_ref, &status);
    if (ret != noErr) {
        msg_Err(crd, "Error evaluating trust");
        result = VLC_EGENERIC;
        goto out;
    }

    CFArrayRef cert_chain = NULL;
    CSSM_TP_APPLE_EVIDENCE_INFO *status_chain;
    ret = SecTrustGetResult(trust_ref, &status, &cert_chain, &status_chain);
    if (ret != noErr || !cert_chain) {
        msg_Err(crd, "error while getting certificate chain");
        result = VLC_EGENERIC;
        goto out;
    }

    CFIndex num_cert_chain = CFArrayGetCount(cert_chain);

    /* Build up the certificate chain array expected by SSLSetCertificate */
    CFMutableArrayRef server_cert_chain = CFArrayCreateMutable(kCFAllocatorDefault, num_cert_chain, &kCFTypeArrayCallBacks);
    CFArrayAppendValue(server_cert_chain, cert_identity);

    msg_Dbg(crd, "Found certificate chain with %ld entries for server certificate", num_cert_chain);
    if (num_cert_chain > 1)
        CFArrayAppendArray(server_cert_chain, cert_chain, CFRangeMake(1, num_cert_chain - 1));
    CFRelease(cert_chain);

    vlc_tls_creds_sys_t *sys = malloc(sizeof(*sys));
    if (unlikely(sys == NULL)) {
        CFRelease(server_cert_chain);
        result = VLC_ENOMEM;
        goto out;
    }

    sys->server_cert_chain = server_cert_chain;
    sys->whitelist = NULL;

    crd->ops = &st_ServerOps;
    crd->sys = sys;

out:
    if (policy)
        CFRelease(policy);
    if (trust_ref)
        CFRelease(trust_ref);

    if (certificate)
        CFRelease(certificate);
    if (cert_identity)
        CFRelease(cert_identity);

    return result;
}