#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  context_t ;
struct TYPE_6__ {int /*<<< orphan*/ * hCertStore; int /*<<< orphan*/  pCertInfo; int /*<<< orphan*/  cbCertEncoded; int /*<<< orphan*/  pbCertEncoded; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; TYPE_2__ ctx; } ;
typedef  TYPE_1__ cert_t ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CERT_CONTEXT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  CertFreeCertificateContext (TYPE_2__*) ; 
 int /*<<< orphan*/  Context_CopyProperties (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ Context_CreateDataContext (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Context_CreateLinkContext (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_CERT_TO_BE_SIGNED ; 
 int /*<<< orphan*/  cert_vtbl ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static context_t *Cert_clone(context_t *context, WINECRYPT_CERTSTORE *store, BOOL use_link)
{
    cert_t *cert;

    if(use_link) {
        cert = (cert_t*)Context_CreateLinkContext(sizeof(CERT_CONTEXT), context, store);
        if(!cert)
            return NULL;
    }else {
        const cert_t *cloned = (const cert_t*)context;
        DWORD size = 0;
        BOOL res;

        cert = (cert_t*)Context_CreateDataContext(sizeof(CERT_CONTEXT), &cert_vtbl, store);
        if(!cert)
            return NULL;

        Context_CopyProperties(&cert->ctx, &cloned->ctx);

        cert->ctx.dwCertEncodingType = cloned->ctx.dwCertEncodingType;
        cert->ctx.pbCertEncoded = CryptMemAlloc(cloned->ctx.cbCertEncoded);
        memcpy(cert->ctx.pbCertEncoded, cloned->ctx.pbCertEncoded, cloned->ctx.cbCertEncoded);
        cert->ctx.cbCertEncoded = cloned->ctx.cbCertEncoded;

        /* FIXME: We don't need to decode the object here, we could just clone cert info. */
        res = CryptDecodeObjectEx(cert->ctx.dwCertEncodingType, X509_CERT_TO_BE_SIGNED,
         cert->ctx.pbCertEncoded, cert->ctx.cbCertEncoded, CRYPT_DECODE_ALLOC_FLAG, NULL,
         &cert->ctx.pCertInfo, &size);
        if(!res) {
            CertFreeCertificateContext(&cert->ctx);
            return NULL;
        }
    }

    cert->ctx.hCertStore = store;
    return &cert->base;
}