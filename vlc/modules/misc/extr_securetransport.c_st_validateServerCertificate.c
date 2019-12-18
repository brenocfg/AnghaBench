#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_4__ {TYPE_1__* p_cred; int /*<<< orphan*/  obj; int /*<<< orphan*/  p_context; } ;
typedef  TYPE_2__ vlc_tls_st_t ;
struct TYPE_3__ {void const* whitelist; } ;
typedef  int SecTrustResultType ;
typedef  void const* SecTrustRef ;
typedef  void const* SecCertificateRef ;
typedef  scalar_t__ OSStatus ;
typedef  void const* CFStringRef ;
typedef  scalar_t__ CFIndex ;
typedef  void const* CFDictionaryRef ;
typedef  void const* CFArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayAppendValue (void const*,void const*) ; 
 scalar_t__ CFArrayGetCount (void const*) ; 
 void* CFArrayGetValueAtIndex (void const*,scalar_t__) ; 
 void* CFDictionaryCreate (int /*<<< orphan*/ ,void const**,void const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CFDictionaryGetValue (void const*,void const*) ; 
 scalar_t__ CFEqual (void const*,void const*) ; 
 int /*<<< orphan*/  CFRelease (void const*) ; 
 int /*<<< orphan*/  CFRetain (void const*) ; 
 void* CFStringCreateWithCString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* N_ (char*) ; 
 scalar_t__ SSLCopyPeerCertificates (int /*<<< orphan*/ ,void const**) ; 
 scalar_t__ SSLCopyPeerTrust (int /*<<< orphan*/ ,void const**) ; 
 scalar_t__ SecTrustEvaluate (void const*,int*) ; 
 void* SecTrustGetCertificateAtIndex (void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ SecTrustGetCertificateCount (void const*) ; 
 scalar_t__ SecTrustSetAnchorCertificates (void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_DIALOG_QUESTION_WARNING ; 
 int /*<<< orphan*/  _ (char*) ; 
 void const* cfKeyCertificate ; 
 void const* cfKeyHost ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kCFTypeDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
#define  kSecTrustResultDeny 131 
#define  kSecTrustResultProceed 130 
#define  kSecTrustResultRecoverableTrustFailure 129 
#define  kSecTrustResultUnspecified 128 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ noErr ; 
 int vlc_dialog_wait_question (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vlc_gettext (char const*) ; 

__attribute__((used)) static int st_validateServerCertificate (vlc_tls_t *session, const char *hostname) {

    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;
    int result = -1;
    SecCertificateRef leaf_cert = NULL;

    SecTrustRef trust = NULL;
    OSStatus ret = SSLCopyPeerTrust(sys->p_context, &trust);
    if (ret != noErr || trust == NULL) {
        msg_Err(sys->obj, "error getting certifictate chain");
        return -1;
    }

    CFStringRef cfHostname = CFStringCreateWithCString(kCFAllocatorDefault,
                                                       hostname,
                                                       kCFStringEncodingUTF8);


    /* enable default root / anchor certificates */
    ret = SecTrustSetAnchorCertificates(trust, NULL);
    if (ret != noErr) {
        msg_Err(sys->obj, "error setting anchor certificates");
        result = -1;
        goto out;
    }

    SecTrustResultType trust_eval_result = 0;

    ret = SecTrustEvaluate(trust, &trust_eval_result);
    if (ret != noErr) {
        msg_Err(sys->obj, "error calling SecTrustEvaluate");
        result = -1;
        goto out;
    }

    switch (trust_eval_result) {
        case kSecTrustResultUnspecified:
        case kSecTrustResultProceed:
            msg_Dbg(sys->obj, "cerfificate verification successful, result is %d", trust_eval_result);
            result = 0;
            goto out;

        case kSecTrustResultRecoverableTrustFailure:
        case kSecTrustResultDeny:
        default:
            msg_Warn(sys->obj, "cerfificate verification failed, result is %d", trust_eval_result);
    }

    /* get leaf certificate */
    /* SSLCopyPeerCertificates is only available on OSX 10.5 or later */
#if !TARGET_OS_IPHONE
    CFArrayRef cert_chain = NULL;
    ret = SSLCopyPeerCertificates(sys->p_context, &cert_chain);
    if (ret != noErr || !cert_chain) {
        result = -1;
        goto out;
    }

    if (CFArrayGetCount(cert_chain) == 0) {
        CFRelease(cert_chain);
        result = -1;
        goto out;
    }

    leaf_cert = (SecCertificateRef)CFArrayGetValueAtIndex(cert_chain, 0);
    CFRetain(leaf_cert);
    CFRelease(cert_chain);
#else
    /* SecTrustGetCertificateAtIndex is only available on 10.7 or iOS */
    if (SecTrustGetCertificateCount(trust) == 0) {
        result = -1;
        goto out;
    }

    leaf_cert = SecTrustGetCertificateAtIndex(trust, 0);
    CFRetain(leaf_cert);
#endif


    /* check if leaf already accepted */
    CFIndex max = CFArrayGetCount(sys->p_cred->whitelist);
    for (CFIndex i = 0; i < max; ++i) {
        CFDictionaryRef dict = CFArrayGetValueAtIndex(sys->p_cred->whitelist, i);
        CFStringRef knownHost = (CFStringRef)CFDictionaryGetValue(dict, cfKeyHost);
        SecCertificateRef knownCert = (SecCertificateRef)CFDictionaryGetValue(dict, cfKeyCertificate);

        if (!knownHost || !knownCert)
            continue;

        if (CFEqual(knownHost, cfHostname) && CFEqual(knownCert, leaf_cert)) {
            msg_Warn(sys->obj, "certificate already accepted, continuing");
            result = 0;
            goto out;
        }
    }

    /* We do not show more certificate details yet because there is no proper API to get
       a summary of the certificate. SecCertificateCopySubjectSummary is the only method
       available on iOS and 10.6. More promising API functions such as
       SecCertificateCopyLongDescription also print out the subject only, more or less.
       But only showing the certificate subject is of no real help for the user.
       We could use SecCertificateCopyValues, but then we need to parse all OID values for
       ourself. This is too mad for just printing information the user will never check
       anyway.
     */

    const char *msg = N_("You attempted to reach %s. "
             "However the security certificate presented by the server "
             "is unknown and could not be authenticated by any trusted "
             "Certification Authority. "
             "This problem may be caused by a configuration error "
             "or an attempt to breach your security or your privacy.\n\n"
             "If in doubt, abort now.\n");
    int answer = vlc_dialog_wait_question(sys->obj,
                                          VLC_DIALOG_QUESTION_WARNING, _("Abort"),
                                          _("Accept certificate temporarily"),
                                          NULL, _("Insecure site"),
                                          vlc_gettext (msg), hostname);
    if (answer == 1) {
        msg_Warn(sys->obj, "Proceeding despite of failed certificate validation");

        /* save leaf certificate in whitelist */
        const void *keys[] = {cfKeyHost, cfKeyCertificate};
        const void *values[] = {cfHostname, leaf_cert};
        CFDictionaryRef dict = CFDictionaryCreate(kCFAllocatorDefault,
                                                   keys, values, 2,
                                                   &kCFTypeDictionaryKeyCallBacks,
                                                   &kCFTypeDictionaryValueCallBacks);
        if (!dict) {
            msg_Err(sys->obj, "error creating dict");
            result = -1;
            goto out;
        }

        CFArrayAppendValue(sys->p_cred->whitelist, dict);
        CFRelease(dict);

        result = 0;
        goto out;

    } else {
        result = -1;
        goto out;
    }

out:
    CFRelease(trust);

    if (cfHostname)
        CFRelease(cfHostname);
    if (leaf_cert)
        CFRelease(leaf_cert);

    return result;
}