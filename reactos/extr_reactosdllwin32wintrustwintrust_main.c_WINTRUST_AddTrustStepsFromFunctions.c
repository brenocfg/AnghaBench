#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wintrust_step {int /*<<< orphan*/  error_index; scalar_t__ func; } ;
struct TYPE_3__ {scalar_t__ pfnFinalPolicy; scalar_t__ pfnCertificateTrust; scalar_t__ pfnSignatureTrust; scalar_t__ pfnObjectTrust; scalar_t__ pfnInitialize; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CRYPT_PROVIDER_FUNCTIONS ;

/* Variables and functions */
 int /*<<< orphan*/  TRUSTERROR_STEP_FINAL_CERTPROV ; 
 int /*<<< orphan*/  TRUSTERROR_STEP_FINAL_OBJPROV ; 
 int /*<<< orphan*/  TRUSTERROR_STEP_FINAL_POLICYPROV ; 
 int /*<<< orphan*/  TRUSTERROR_STEP_FINAL_SIGPROV ; 
 int /*<<< orphan*/  TRUSTERROR_STEP_FINAL_WVTINIT ; 

__attribute__((used)) static DWORD WINTRUST_AddTrustStepsFromFunctions(struct wintrust_step *steps,
 const CRYPT_PROVIDER_FUNCTIONS *psPfns)
{
    DWORD numSteps = 0;

    if (psPfns->pfnInitialize)
    {
        steps[numSteps].func = psPfns->pfnInitialize;
        steps[numSteps++].error_index = TRUSTERROR_STEP_FINAL_WVTINIT;
    }
    if (psPfns->pfnObjectTrust)
    {
        steps[numSteps].func = psPfns->pfnObjectTrust;
        steps[numSteps++].error_index = TRUSTERROR_STEP_FINAL_OBJPROV;
    }
    if (psPfns->pfnSignatureTrust)
    {
        steps[numSteps].func = psPfns->pfnSignatureTrust;
        steps[numSteps++].error_index = TRUSTERROR_STEP_FINAL_SIGPROV;
    }
    if (psPfns->pfnCertificateTrust)
    {
        steps[numSteps].func = psPfns->pfnCertificateTrust;
        steps[numSteps++].error_index = TRUSTERROR_STEP_FINAL_CERTPROV;
    }
    if (psPfns->pfnFinalPolicy)
    {
        steps[numSteps].func = psPfns->pfnFinalPolicy;
        steps[numSteps++].error_index = TRUSTERROR_STEP_FINAL_POLICYPROV;
    }
    return numSteps;
}