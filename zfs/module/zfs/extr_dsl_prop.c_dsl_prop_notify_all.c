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
struct TYPE_5__ {int /*<<< orphan*/  dp_config_rwlock; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  dd_object; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int /*<<< orphan*/  RRW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_find_dp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_prop_notify_all_cb ; 

void
dsl_prop_notify_all(dsl_dir_t *dd)
{
	dsl_pool_t *dp = dd->dd_pool;
	ASSERT(RRW_WRITE_HELD(&dp->dp_config_rwlock));
	(void) dmu_objset_find_dp(dp, dd->dd_object, dsl_prop_notify_all_cb,
	    NULL, DS_FIND_CHILDREN);
}