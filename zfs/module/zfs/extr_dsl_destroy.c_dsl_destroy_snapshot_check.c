#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_2__ {char* ddsa_name; int /*<<< orphan*/  ddsa_defer; } ;
typedef  TYPE_1__ dsl_destroy_snapshot_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_destroy_snapshot_check_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_destroy_snapshot_check(void *arg, dmu_tx_t *tx)
{
	dsl_destroy_snapshot_arg_t *ddsa = arg;
	const char *dsname = ddsa->ddsa_name;
	boolean_t defer = ddsa->ddsa_defer;

	dsl_pool_t *dp = dmu_tx_pool(tx);
	int error = 0;
	dsl_dataset_t *ds;

	error = dsl_dataset_hold(dp, dsname, FTAG, &ds);

	/*
	 * If the snapshot does not exist, silently ignore it, and
	 * dsl_destroy_snapshot_sync() will be a no-op
	 * (it's "already destroyed").
	 */
	if (error == ENOENT)
		return (0);

	if (error == 0) {
		error = dsl_destroy_snapshot_check_impl(ds, defer);
		dsl_dataset_rele(ds, FTAG);
	}

	return (error);
}