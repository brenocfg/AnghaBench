#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t cLowerQualityChainContext; int /*<<< orphan*/ * rgpLowerQualityChainContext; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CertificateChain ;

/* Variables and functions */
 int /*<<< orphan*/  CertFreeCertificateChain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CRYPT_FreeLowerQualityChains(CertificateChain *chain)
{
    DWORD i;

    for (i = 0; i < chain->context.cLowerQualityChainContext; i++)
        CertFreeCertificateChain(chain->context.rgpLowerQualityChainContext[i]);
    CryptMemFree(chain->context.rgpLowerQualityChainContext);
    chain->context.cLowerQualityChainContext = 0;
    chain->context.rgpLowerQualityChainContext = NULL;
}