#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CRYPT_HASH_BLOB ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_SIGNATURE_HASH_PROP_ID ; 
 int CertGetCertificateContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL compare_cert_by_signature_hash(PCCERT_CONTEXT pCertContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    const CRYPT_HASH_BLOB *hash = pvPara;
    DWORD size = 0;
    BOOL ret;

    ret = CertGetCertificateContextProperty(pCertContext,
     CERT_SIGNATURE_HASH_PROP_ID, NULL, &size);
    if (ret && size == hash->cbData)
    {
        LPBYTE buf = CryptMemAlloc(size);

        if (buf)
        {
            CertGetCertificateContextProperty(pCertContext,
             CERT_SIGNATURE_HASH_PROP_ID, buf, &size);
            ret = !memcmp(buf, hash->pbData, size);
            CryptMemFree(buf);
        }
        else
            ret = FALSE;
    }
    else
        ret = FALSE;
    return ret;
}