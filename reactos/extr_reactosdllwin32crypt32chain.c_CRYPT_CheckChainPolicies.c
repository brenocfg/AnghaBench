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
struct TYPE_9__ {int dwErrorStatus; } ;
struct TYPE_8__ {int /*<<< orphan*/  pCertInfo; } ;
struct TYPE_7__ {int cElement; TYPE_1__** rgpElement; int /*<<< orphan*/  TrustStatus; } ;
struct TYPE_6__ {TYPE_4__ TrustStatus; TYPE_3__* pCertContext; } ;
typedef  TYPE_2__* PCERT_SIMPLE_CHAIN ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CERT_POLICIES_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_CheckPolicies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CRYPT_CombineTrustStatus (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * CRYPT_GetPolicies (TYPE_3__*) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CRYPT_CheckChainPolicies(PCERT_SIMPLE_CHAIN chain)
{
    int i, j;

    for (i = chain->cElement - 1; i > 0; i--)
    {
        CERT_POLICIES_INFO *policies;

        if ((policies = CRYPT_GetPolicies(chain->rgpElement[i]->pCertContext)))
        {
            for (j = i - 1; j >= 0; j--)
            {
                DWORD errorStatus = 0;

                CRYPT_CheckPolicies(policies,
                 chain->rgpElement[j]->pCertContext->pCertInfo, &errorStatus);
                if (errorStatus)
                {
                    chain->rgpElement[i]->TrustStatus.dwErrorStatus |=
                     errorStatus;
                    CRYPT_CombineTrustStatus(&chain->TrustStatus,
                     &chain->rgpElement[i]->TrustStatus);
                }
            }
            LocalFree(policies);
        }
    }
}