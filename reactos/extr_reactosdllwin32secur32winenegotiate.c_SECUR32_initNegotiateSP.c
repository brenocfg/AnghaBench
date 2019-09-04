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
struct TYPE_6__ {int member_1; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int member_1; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SecureProvider ;
typedef  TYPE_1__ SecPkgInfoW ;
typedef  TYPE_2__ SecPkgInfoA ;

/* Variables and functions */
 int /*<<< orphan*/  CAPS ; 
 int /*<<< orphan*/  NEGO_MAX_TOKEN ; 
 int /*<<< orphan*/  RPC_C_AUTHN_GSS_NEGOTIATE ; 
 int /*<<< orphan*/  SECUR32_addPackages (int /*<<< orphan*/ *,long,TYPE_2__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * SECUR32_addProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  negoTableA ; 
 int /*<<< orphan*/  negoTableW ; 
 int /*<<< orphan*/  nego_name_A ; 
 int /*<<< orphan*/  nego_name_W ; 
 int /*<<< orphan*/  negotiate_comment_A ; 
 int /*<<< orphan*/  negotiate_comment_W ; 

void SECUR32_initNegotiateSP(void)
{
    SecureProvider *provider = SECUR32_addProvider(&negoTableA, &negoTableW, NULL);

    const SecPkgInfoW infoW = {CAPS, 1, RPC_C_AUTHN_GSS_NEGOTIATE, NEGO_MAX_TOKEN,
                               nego_name_W, negotiate_comment_W};
    const SecPkgInfoA infoA = {CAPS, 1, RPC_C_AUTHN_GSS_NEGOTIATE, NEGO_MAX_TOKEN,
                               nego_name_A, negotiate_comment_A};
    SECUR32_addPackages(provider, 1L, &infoA, &infoW);
}