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
struct TYPE_3__ {scalar_t__ dwFlags; scalar_t__ dwSessionLifespan; scalar_t__ dwMaximumCipherStrength; scalar_t__ dwMinimumCipherStrength; scalar_t__ grbitEnabledProtocols; int /*<<< orphan*/ * palgSupportedAlgs; scalar_t__ cSupportedAlgs; int /*<<< orphan*/ * aphMappers; scalar_t__ cMappers; int /*<<< orphan*/ * hRootStore; scalar_t__ paCred; scalar_t__ cCreds; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__ SCHANNEL_CRED ;

/* Variables and functions */
 int /*<<< orphan*/  SCHANNEL_CRED_VERSION ; 

__attribute__((used)) static void init_cred(SCHANNEL_CRED *cred)
{
    cred->dwVersion = SCHANNEL_CRED_VERSION;
    cred->cCreds = 0;
    cred->paCred = 0;
    cred->hRootStore = NULL;
    cred->cMappers = 0;
    cred->aphMappers = NULL;
    cred->cSupportedAlgs = 0;
    cred->palgSupportedAlgs = NULL;
    cred->grbitEnabledProtocols = 0;
    cred->dwMinimumCipherStrength = 0;
    cred->dwMaximumCipherStrength = 0;
    cred->dwSessionLifespan = 0;
    cred->dwFlags = 0;
}