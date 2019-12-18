#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_livelist_delete_zthr; int /*<<< orphan*/  spa_livelists_to_delete; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_14__ {TYPE_3__* dp_free_dir; TYPE_1__* dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  dd_livelist; int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_3__ dsl_dir_t ;
struct TYPE_16__ {TYPE_3__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_17__ {int /*<<< orphan*/  dd_uncompressed_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DD_FIELD_LIVELIST ; 
 int /*<<< orphan*/  DD_USED_HEAD ; 
 int /*<<< orphan*/  DMU_OTN_ZAP_METADATA ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_POOL_DELETED_CLONES ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int ENOENT ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 int dmu_objset_from_ds (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_zil (int /*<<< orphan*/ *) ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_clone_destroy_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* dsl_dir_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dir_remove_livelist (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zap_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_panic_recover (char*) ; 
 int /*<<< orphan*/  zil_destroy_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zthr_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_async_clone_destroy(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	uint64_t zap_obj, to_delete, used, comp, uncomp;
	objset_t *os;
	dsl_dir_t *dd = ds->ds_dir;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;
	VERIFY0(dmu_objset_from_ds(ds, &os));

	/* Check that the clone is in a correct state to be deleted */
	dsl_clone_destroy_assert(dd);

	/* Destroy the zil */
	zil_destroy_sync(dmu_objset_zil(os), tx);

	VERIFY0(zap_lookup(mos, dd->dd_object,
	    DD_FIELD_LIVELIST, sizeof (uint64_t), 1, &to_delete));
	/* Initialize deleted_clones entry to track livelists to cleanup */
	int error = zap_lookup(mos, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_DELETED_CLONES, sizeof (uint64_t), 1, &zap_obj);
	if (error == ENOENT) {
		zap_obj = zap_create(mos, DMU_OTN_ZAP_METADATA,
		    DMU_OT_NONE, 0, tx);
		VERIFY0(zap_add(mos, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_DELETED_CLONES, sizeof (uint64_t), 1,
		    &(zap_obj), tx));
		spa->spa_livelists_to_delete = zap_obj;
	} else if (error != 0) {
		zfs_panic_recover("zfs: error %d was returned while looking "
		    "up DMU_POOL_DELETED_CLONES in the zap");
		return;
	}
	VERIFY0(zap_add_int(mos, zap_obj, to_delete, tx));

	/* Clone is no longer using space, now tracked by dp_free_dir */
	dsl_deadlist_space(&dd->dd_livelist, &used, &comp, &uncomp);
	dsl_dir_diduse_space(dd, DD_USED_HEAD,
	    -used, -comp, -dsl_dir_phys(dd)->dd_uncompressed_bytes,
	    tx);
	dsl_dir_diduse_space(dp->dp_free_dir, DD_USED_HEAD,
	    used, comp, uncomp, tx);
	dsl_dir_remove_livelist(dd, tx, B_FALSE);
	zthr_wakeup(spa->spa_livelist_delete_zthr);
}