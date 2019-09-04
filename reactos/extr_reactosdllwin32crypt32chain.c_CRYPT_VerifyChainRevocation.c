#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  revocationStatus ;
typedef  int /*<<< orphan*/  revocationPara ;
struct TYPE_24__ {int cbSize; int /*<<< orphan*/  dwRevocationFreshnessTime; int /*<<< orphan*/  fCheckRevocationFreshnessTime; int /*<<< orphan*/  dwUrlRetrievalTimeout; } ;
struct TYPE_23__ {int member_0; int cCertStore; int /*<<< orphan*/ * pIssuerCert; int /*<<< orphan*/  dwFreshnessTime; int /*<<< orphan*/  fCheckFreshnessTime; int /*<<< orphan*/  dwUrlRetrievalTimeout; scalar_t__ hCrlStore; scalar_t__* rgCertStore; int /*<<< orphan*/  pftTimeToUse; int /*<<< orphan*/  member_1; } ;
struct TYPE_22__ {int member_0; int dwError; int /*<<< orphan*/  member_1; } ;
struct TYPE_19__ {int dwErrorStatus; } ;
struct TYPE_21__ {int cChain; TYPE_4__ TrustStatus; TYPE_2__** rgpChain; } ;
struct TYPE_18__ {int dwErrorStatus; } ;
struct TYPE_20__ {TYPE_3__ TrustStatus; } ;
struct TYPE_17__ {int cElement; TYPE_1__** rgpElement; } ;
struct TYPE_16__ {int /*<<< orphan*/ * pCertContext; } ;
typedef  TYPE_5__* PCERT_CHAIN_ELEMENT ;
typedef  TYPE_6__* PCERT_CHAIN_CONTEXT ;
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  scalar_t__ HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_7__ CERT_REVOCATION_STATUS ;
typedef  TYPE_8__ CERT_REVOCATION_PARA ;
typedef  TYPE_9__ CERT_CHAIN_PARA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CERT_CHAIN_REVOCATION_ACCUMULATIVE_TIMEOUT ; 
 int CERT_CHAIN_REVOCATION_CHECK_CACHE_ONLY ; 
 int CERT_CHAIN_REVOCATION_CHECK_CHAIN ; 
 int CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT ; 
 int CERT_CHAIN_REVOCATION_CHECK_END_CERT ; 
 int /*<<< orphan*/  CERT_CONTEXT_REVOCATION_TYPE ; 
 int CERT_TRUST_IS_OFFLINE_REVOCATION ; 
 int CERT_TRUST_IS_REVOKED ; 
 int CERT_TRUST_REVOCATION_STATUS_UNKNOWN ; 
 int CERT_VERIFY_CACHE_ONLY_BASED_REVOCATION ; 
 int CERT_VERIFY_REV_ACCUMULATIVE_TIMEOUT_FLAG ; 
 int CERT_VERIFY_REV_CHAIN_FLAG ; 
#define  CRYPT_E_NOT_IN_REVOCATION_DATABASE 132 
#define  CRYPT_E_NO_REVOCATION_CHECK 131 
#define  CRYPT_E_NO_REVOCATION_DLL 130 
#define  CRYPT_E_REVOCATION_OFFLINE 129 
#define  CRYPT_E_REVOKED 128 
 TYPE_5__* CRYPT_FindIthElementInChain (TYPE_6__*,int) ; 
 int /*<<< orphan*/  CertVerifyRevocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,int,TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static void CRYPT_VerifyChainRevocation(PCERT_CHAIN_CONTEXT chain,
 LPFILETIME pTime, HCERTSTORE hAdditionalStore,
 const CERT_CHAIN_PARA *pChainPara, DWORD chainFlags)
{
    DWORD cContext;

    if (chainFlags & CERT_CHAIN_REVOCATION_CHECK_END_CERT)
        cContext = 1;
    else if ((chainFlags & CERT_CHAIN_REVOCATION_CHECK_CHAIN) ||
     (chainFlags & CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT))
    {
        DWORD i;

        for (i = 0, cContext = 0; i < chain->cChain; i++)
        {
            if (i < chain->cChain - 1 ||
             chainFlags & CERT_CHAIN_REVOCATION_CHECK_CHAIN)
                cContext += chain->rgpChain[i]->cElement;
            else
                cContext += chain->rgpChain[i]->cElement - 1;
        }
    }
    else
        cContext = 0;
    if (cContext)
    {
        DWORD i, j, iContext, revocationFlags;
        CERT_REVOCATION_PARA revocationPara = { sizeof(revocationPara), 0 };
        CERT_REVOCATION_STATUS revocationStatus =
         { sizeof(revocationStatus), 0 };
        BOOL ret;

        revocationFlags = CERT_VERIFY_REV_CHAIN_FLAG;
        if (chainFlags & CERT_CHAIN_REVOCATION_CHECK_CACHE_ONLY)
            revocationFlags |= CERT_VERIFY_CACHE_ONLY_BASED_REVOCATION;
        if (chainFlags & CERT_CHAIN_REVOCATION_ACCUMULATIVE_TIMEOUT)
            revocationFlags |= CERT_VERIFY_REV_ACCUMULATIVE_TIMEOUT_FLAG;
        revocationPara.pftTimeToUse = pTime;
        if (hAdditionalStore)
        {
            revocationPara.cCertStore = 1;
            revocationPara.rgCertStore = &hAdditionalStore;
            revocationPara.hCrlStore = hAdditionalStore;
        }
        if (pChainPara->cbSize == sizeof(CERT_CHAIN_PARA))
        {
            revocationPara.dwUrlRetrievalTimeout =
             pChainPara->dwUrlRetrievalTimeout;
            revocationPara.fCheckFreshnessTime =
             pChainPara->fCheckRevocationFreshnessTime;
            revocationPara.dwFreshnessTime =
             pChainPara->dwRevocationFreshnessTime;
        }
        for (i = 0, iContext = 0; iContext < cContext && i < chain->cChain; i++)
        {
            for (j = 0; iContext < cContext &&
             j < chain->rgpChain[i]->cElement; j++, iContext++)
            {
                PCCERT_CONTEXT certToCheck =
                 chain->rgpChain[i]->rgpElement[j]->pCertContext;

                if (j < chain->rgpChain[i]->cElement - 1)
                    revocationPara.pIssuerCert =
                     chain->rgpChain[i]->rgpElement[j + 1]->pCertContext;
                else
                    revocationPara.pIssuerCert = NULL;
                ret = CertVerifyRevocation(X509_ASN_ENCODING,
                 CERT_CONTEXT_REVOCATION_TYPE, 1, (void **)&certToCheck,
                 revocationFlags, &revocationPara, &revocationStatus);

                if (!ret && chainFlags & CERT_CHAIN_REVOCATION_CHECK_CHAIN
                    && revocationStatus.dwError == CRYPT_E_NO_REVOCATION_CHECK && revocationPara.pIssuerCert == NULL)
                    ret = TRUE;

                if (!ret)
                {
                    PCERT_CHAIN_ELEMENT element = CRYPT_FindIthElementInChain(
                     chain, iContext);
                    DWORD error;

                    switch (revocationStatus.dwError)
                    {
                    case CRYPT_E_NO_REVOCATION_CHECK:
                    case CRYPT_E_NO_REVOCATION_DLL:
                    case CRYPT_E_NOT_IN_REVOCATION_DATABASE:
                        /* If the revocation status is unknown, it's assumed
                         * to be offline too.
                         */
                        error = CERT_TRUST_REVOCATION_STATUS_UNKNOWN |
                         CERT_TRUST_IS_OFFLINE_REVOCATION;
                        break;
                    case CRYPT_E_REVOCATION_OFFLINE:
                        error = CERT_TRUST_IS_OFFLINE_REVOCATION;
                        break;
                    case CRYPT_E_REVOKED:
                        error = CERT_TRUST_IS_REVOKED;
                        break;
                    default:
                        WARN("unmapped error %08x\n", revocationStatus.dwError);
                        error = 0;
                    }
                    if (element)
                    {
                        /* FIXME: set element's pRevocationInfo member */
                        element->TrustStatus.dwErrorStatus |= error;
                    }
                    chain->TrustStatus.dwErrorStatus |= error;
                }
            }
        }
    }
}