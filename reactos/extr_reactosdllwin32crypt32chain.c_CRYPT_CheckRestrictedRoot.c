#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  scalar_t__ HCERTSTORE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPT_FindCertInStore (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertEnumCertificatesInStore (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ *) ; 
 scalar_t__ CertOpenSystemStoreW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  rootW ; 

__attribute__((used)) static BOOL CRYPT_CheckRestrictedRoot(HCERTSTORE store)
{
    BOOL ret = TRUE;

    if (store)
    {
        HCERTSTORE rootStore = CertOpenSystemStoreW(0, rootW);
        PCCERT_CONTEXT cert = NULL, check;

        do {
            cert = CertEnumCertificatesInStore(store, cert);
            if (cert)
            {
                if (!(check = CRYPT_FindCertInStore(rootStore, cert)))
                    ret = FALSE;
                else
                    CertFreeCertificateContext(check);
            }
        } while (ret && cert);
        if (cert)
            CertFreeCertificateContext(cert);
        CertCloseStore(rootStore, 0);
    }
    return ret;
}