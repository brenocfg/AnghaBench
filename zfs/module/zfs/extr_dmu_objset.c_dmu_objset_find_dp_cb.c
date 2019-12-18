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
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dc_dp; } ;
typedef  TYPE_1__ dmu_objset_find_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dmu_objset_find_dp_impl (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_pool_config_enter_prio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_objset_find_dp_cb(void *arg)
{
	dmu_objset_find_ctx_t *dcp = arg;
	dsl_pool_t *dp = dcp->dc_dp;

	/*
	 * We need to get a pool_config_lock here, as there are several
	 * assert(pool_config_held) down the stack. Getting a lock via
	 * dsl_pool_config_enter is risky, as it might be stalled by a
	 * pending writer. This would deadlock, as the write lock can
	 * only be granted when our parent thread gives up the lock.
	 * The _prio interface gives us priority over a pending writer.
	 */
	dsl_pool_config_enter_prio(dp, FTAG);

	dmu_objset_find_dp_impl(dcp);

	dsl_pool_config_exit(dp, FTAG);
}