#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ds_bp_rwlock; TYPE_2__* ds_objset; TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
struct TYPE_12__ {scalar_t__ drc_resumable; scalar_t__ drc_raw; TYPE_3__* drc_ds; } ;
typedef  TYPE_4__ dmu_recv_cookie_t ;
struct TYPE_10__ {int /*<<< orphan*/  os_raw_receive; } ;
struct TYPE_9__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_recv_tag ; 
 int /*<<< orphan*/  dsl_dataset_disown (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_get_blkptr (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dsl_destroy_head (char*) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_recv_cleanup_ds(dmu_recv_cookie_t *drc)
{
	dsl_dataset_t *ds = drc->drc_ds;
	ds_hold_flags_t dsflags = (drc->drc_raw) ? 0 : DS_HOLD_FLAG_DECRYPT;

	/*
	 * Wait for the txg sync before cleaning up the receive. For
	 * resumable receives, this ensures that our resume state has
	 * been written out to disk. For raw receives, this ensures
	 * that the user accounting code will not attempt to do anything
	 * after we stopped receiving the dataset.
	 */
	txg_wait_synced(ds->ds_dir->dd_pool, 0);
	ds->ds_objset->os_raw_receive = B_FALSE;

	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	if (drc->drc_resumable && !BP_IS_HOLE(dsl_dataset_get_blkptr(ds))) {
		rrw_exit(&ds->ds_bp_rwlock, FTAG);
		dsl_dataset_disown(ds, dsflags, dmu_recv_tag);
	} else {
		char name[ZFS_MAX_DATASET_NAME_LEN];
		rrw_exit(&ds->ds_bp_rwlock, FTAG);
		dsl_dataset_name(ds, name);
		dsl_dataset_disown(ds, dsflags, dmu_recv_tag);
		(void) dsl_destroy_head(name);
	}
}