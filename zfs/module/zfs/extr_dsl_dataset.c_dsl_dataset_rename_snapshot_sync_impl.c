#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  dp_spa; int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_16__ {int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_snapname; int /*<<< orphan*/  ds_lock; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_17__ {int /*<<< orphan*/  ddrsa_newsnapname; int /*<<< orphan*/  ddrsa_oldsnapname; int /*<<< orphan*/ * ddrsa_tx; } ;
typedef  TYPE_3__ dsl_dataset_rename_snapshot_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_snapnames_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_10__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dsl_dataset_snap_lookup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_snap_remove (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_2__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_rename_minors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_dataset_rename_snapshot_sync_impl(dsl_pool_t *dp,
    dsl_dataset_t *hds, void *arg)
{
	dsl_dataset_rename_snapshot_arg_t *ddrsa = arg;
	dsl_dataset_t *ds;
	uint64_t val;
	dmu_tx_t *tx = ddrsa->ddrsa_tx;
	int error;

	error = dsl_dataset_snap_lookup(hds, ddrsa->ddrsa_oldsnapname, &val);
	ASSERT(error == 0 || error == ENOENT);
	if (error == ENOENT) {
		/* ignore nonexistent snapshots */
		return (0);
	}

	VERIFY0(dsl_dataset_hold_obj(dp, val, FTAG, &ds));

	/* log before we change the name */
	spa_history_log_internal_ds(ds, "rename", tx,
	    "-> @%s", ddrsa->ddrsa_newsnapname);

	VERIFY0(dsl_dataset_snap_remove(hds, ddrsa->ddrsa_oldsnapname, tx,
	    B_FALSE));
	mutex_enter(&ds->ds_lock);
	(void) strlcpy(ds->ds_snapname, ddrsa->ddrsa_newsnapname,
	    sizeof (ds->ds_snapname));
	mutex_exit(&ds->ds_lock);
	VERIFY0(zap_add(dp->dp_meta_objset,
	    dsl_dataset_phys(hds)->ds_snapnames_zapobj,
	    ds->ds_snapname, 8, 1, &ds->ds_object, tx));
	zvol_rename_minors(dp->dp_spa, ddrsa->ddrsa_oldsnapname,
	    ddrsa->ddrsa_newsnapname, B_TRUE);

	dsl_dataset_rele(ds, FTAG);
	return (0);
}