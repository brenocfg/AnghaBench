#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_13__ {int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_os; } ;
typedef  TYPE_2__ dsl_deadlist_t ;
typedef  int /*<<< orphan*/  dsl_deadlist_phys_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {scalar_t__ doi_type; } ;
typedef  TYPE_3__ dmu_object_info_t ;
struct TYPE_16__ {int /*<<< orphan*/ * db_data; } ;
typedef  TYPE_4__ dmu_buf_t ;
typedef  int /*<<< orphan*/  bpobj_t ;

/* Variables and functions */
 scalar_t__ DMU_OT_BPOBJ ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_bonus_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_insert_bpobj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_insert_cb ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zap_remove_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_strtonum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_deadlist_merge(dsl_deadlist_t *dl, uint64_t obj, dmu_tx_t *tx)
{
	zap_cursor_t zc;
	zap_attribute_t za;
	dmu_buf_t *bonus;
	dsl_deadlist_phys_t *dlp;
	dmu_object_info_t doi;

	VERIFY0(dmu_object_info(dl->dl_os, obj, &doi));
	if (doi.doi_type == DMU_OT_BPOBJ) {
		bpobj_t bpo;
		VERIFY0(bpobj_open(&bpo, dl->dl_os, obj));
		VERIFY0(bpobj_iterate(&bpo, dsl_deadlist_insert_cb, dl, tx));
		bpobj_close(&bpo);
		return;
	}

	mutex_enter(&dl->dl_lock);
	for (zap_cursor_init(&zc, dl->dl_os, obj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		uint64_t mintxg = zfs_strtonum(za.za_name, NULL);
		dsl_deadlist_insert_bpobj(dl, za.za_first_integer, mintxg, tx);
		VERIFY0(zap_remove_int(dl->dl_os, obj, mintxg, tx));
	}
	zap_cursor_fini(&zc);

	VERIFY0(dmu_bonus_hold(dl->dl_os, obj, FTAG, &bonus));
	dlp = bonus->db_data;
	dmu_buf_will_dirty(bonus, tx);
	bzero(dlp, sizeof (*dlp));
	dmu_buf_rele(bonus, FTAG);
	mutex_exit(&dl->dl_lock);
}