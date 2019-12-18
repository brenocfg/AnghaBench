#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_11__ {scalar_t__ zb_objset; } ;
struct TYPE_8__ {TYPE_7__ scn_bookmark; int /*<<< orphan*/  scn_flags; } ;
typedef  TYPE_1__ dsl_scan_phys_t ;
struct TYPE_9__ {scalar_t__ ds_object; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_10__ {scalar_t__ ds_next_snap_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSF_VISIT_DS_AGAIN ; 
 int /*<<< orphan*/  SET_BOOKMARK (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZB_DESTROYED_OBJSET ; 
 TYPE_3__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
ds_destroyed_scn_phys(dsl_dataset_t *ds, dsl_scan_phys_t *scn_phys)
{
	if (scn_phys->scn_bookmark.zb_objset == ds->ds_object) {
		if (ds->ds_is_snapshot) {
			/*
			 * Note:
			 *  - scn_cur_{min,max}_txg stays the same.
			 *  - Setting the flag is not really necessary if
			 *    scn_cur_max_txg == scn_max_txg, because there
			 *    is nothing after this snapshot that we care
			 *    about.  However, we set it anyway and then
			 *    ignore it when we retraverse it in
			 *    dsl_scan_visitds().
			 */
			scn_phys->scn_bookmark.zb_objset =
			    dsl_dataset_phys(ds)->ds_next_snap_obj;
			zfs_dbgmsg("destroying ds %llu; currently traversing; "
			    "reset zb_objset to %llu",
			    (u_longlong_t)ds->ds_object,
			    (u_longlong_t)dsl_dataset_phys(ds)->
			    ds_next_snap_obj);
			scn_phys->scn_flags |= DSF_VISIT_DS_AGAIN;
		} else {
			SET_BOOKMARK(&scn_phys->scn_bookmark,
			    ZB_DESTROYED_OBJSET, 0, 0, 0);
			zfs_dbgmsg("destroying ds %llu; currently traversing; "
			    "reset bookmark to -1,0,0,0",
			    (u_longlong_t)ds->ds_object);
		}
	}
}