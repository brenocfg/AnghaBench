#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_meta_rootbp; } ;
typedef  TYPE_1__ dsl_pool_t ;

/* Variables and functions */
 int dmu_objset_open_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_close (TYPE_1__*) ; 
 TYPE_1__* dsl_pool_open_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_pool_init(spa_t *spa, uint64_t txg, dsl_pool_t **dpp)
{
	int err;
	dsl_pool_t *dp = dsl_pool_open_impl(spa, txg);

	/*
	 * Initialize the caller's dsl_pool_t structure before we actually open
	 * the meta objset.  This is done because a self-healing write zio may
	 * be issued as part of dmu_objset_open_impl() and the spa needs its
	 * dsl_pool_t initialized in order to handle the write.
	 */
	*dpp = dp;

	err = dmu_objset_open_impl(spa, NULL, &dp->dp_meta_rootbp,
	    &dp->dp_meta_objset);
	if (err != 0) {
		dsl_pool_close(dp);
		*dpp = NULL;
	}

	return (err);
}