#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* sa_update_cb ) (TYPE_2__*,int /*<<< orphan*/ *) ;scalar_t__ sa_need_attr_registration; } ;
typedef  TYPE_1__ sa_os_t ;
struct TYPE_12__ {int /*<<< orphan*/ * sa_spill; int /*<<< orphan*/ * sa_spill_tab; TYPE_4__* sa_os; int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_2__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_13__ {TYPE_1__* os_sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_SA_BONUSTYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_BONUS ; 
 int /*<<< orphan*/  SA_BONUSTYPE_FROM_DB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_GET_DB (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_UPDATE ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sa_attr_op (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_attr_register_sync (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_idx_tab_rele (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sa_bulk_update_impl(sa_handle_t *hdl, sa_bulk_attr_t *bulk, int count,
    dmu_tx_t *tx)
{
	int error;
	sa_os_t *sa = hdl->sa_os->os_sa;
	dmu_object_type_t bonustype;
	dmu_buf_t *saved_spill;

	ASSERT(hdl);
	ASSERT(MUTEX_HELD(&hdl->sa_lock));

	bonustype = SA_BONUSTYPE_FROM_DB(SA_GET_DB(hdl, SA_BONUS));
	saved_spill = hdl->sa_spill;

	/* sync out registration table if necessary */
	if (sa->sa_need_attr_registration)
		sa_attr_register_sync(hdl, tx);

	error = sa_attr_op(hdl, bulk, count, SA_UPDATE, tx);
	if (error == 0 && !IS_SA_BONUSTYPE(bonustype) && sa->sa_update_cb)
		sa->sa_update_cb(hdl, tx);

	/*
	 * If saved_spill is NULL and current sa_spill is not NULL that
	 * means we increased the refcount of the spill buffer through
	 * sa_get_spill() or dmu_spill_hold_by_dnode().  Therefore we
	 * must release the hold before calling dmu_tx_commit() to avoid
	 * making a copy of this buffer in dbuf_sync_leaf() due to the
	 * reference count now being greater than 1.
	 */
	if (!saved_spill && hdl->sa_spill) {
		if (hdl->sa_spill_tab) {
			sa_idx_tab_rele(hdl->sa_os, hdl->sa_spill_tab);
			hdl->sa_spill_tab = NULL;
		}

		dmu_buf_rele(hdl->sa_spill, NULL);
		hdl->sa_spill = NULL;
	}

	return (error);
}