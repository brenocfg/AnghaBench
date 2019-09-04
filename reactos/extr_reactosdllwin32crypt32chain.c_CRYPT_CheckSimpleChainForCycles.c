#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwErrorStatus; } ;
struct TYPE_9__ {TYPE_2__ TrustStatus; TYPE_1__* pCertContext; } ;
struct TYPE_8__ {int cElement; TYPE_4__** rgpElement; } ;
struct TYPE_6__ {int /*<<< orphan*/  pCertInfo; } ;
typedef  TYPE_3__* PCERT_SIMPLE_CHAIN ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_TRUST_INVALID_BASIC_CONSTRAINTS ; 
 int CERT_TRUST_IS_CYCLIC ; 
 int /*<<< orphan*/  CRYPT_FreeChainElement (TYPE_4__*) ; 
 scalar_t__ CertCompareCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static void CRYPT_CheckSimpleChainForCycles(PCERT_SIMPLE_CHAIN chain)
{
    DWORD i, j, cyclicCertIndex = 0;

    /* O(n^2) - I don't think there's a faster way */
    for (i = 0; !cyclicCertIndex && i < chain->cElement; i++)
        for (j = i + 1; !cyclicCertIndex && j < chain->cElement; j++)
            if (CertCompareCertificate(X509_ASN_ENCODING,
             chain->rgpElement[i]->pCertContext->pCertInfo,
             chain->rgpElement[j]->pCertContext->pCertInfo))
                cyclicCertIndex = j;
    if (cyclicCertIndex)
    {
        chain->rgpElement[cyclicCertIndex]->TrustStatus.dwErrorStatus
         |= CERT_TRUST_IS_CYCLIC | CERT_TRUST_INVALID_BASIC_CONSTRAINTS;
        /* Release remaining certs */
        for (i = cyclicCertIndex + 1; i < chain->cElement; i++)
            CRYPT_FreeChainElement(chain->rgpElement[i]);
        /* Truncate chain */
        chain->cElement = cyclicCertIndex + 1;
    }
}