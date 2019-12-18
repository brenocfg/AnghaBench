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
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_6__ {char* ddsa_name; int /*<<< orphan*/  ddsa_defer; } ;
typedef  TYPE_2__ dsl_destroy_snapshot_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_destroy_snapshot_sync_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_remove_minors (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
dsl_destroy_snapshot_sync(void *arg, dmu_tx_t *tx)
{
	dsl_destroy_snapshot_arg_t *ddsa = arg;
	const char *dsname = ddsa->ddsa_name;
	boolean_t defer = ddsa->ddsa_defer;

	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;

	int error = dsl_dataset_hold(dp, dsname, FTAG, &ds);
	if (error == ENOENT)
		return;
	ASSERT0(error);
	dsl_destroy_snapshot_sync_impl(ds, defer, tx);
	zvol_remove_minors(dp->dp_spa, dsname, B_TRUE);
	dsl_dataset_rele(ds, FTAG);
}