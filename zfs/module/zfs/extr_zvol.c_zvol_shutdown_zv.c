#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int zv_flags; int /*<<< orphan*/  zv_objset; int /*<<< orphan*/ * zv_dn; int /*<<< orphan*/ * zv_zilog; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_state_lock; } ;
typedef  TYPE_1__ zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int ZVOL_WRITTEN_TO ; 
 int /*<<< orphan*/  dmu_objset_evict_dbufs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zvol_shutdown_zv(zvol_state_t *zv)
{
	ASSERT(MUTEX_HELD(&zv->zv_state_lock) &&
	    RW_LOCK_HELD(&zv->zv_suspend_lock));

	if (zv->zv_flags & ZVOL_WRITTEN_TO) {
		ASSERT(zv->zv_zilog != NULL);
		zil_close(zv->zv_zilog);
	}

	zv->zv_zilog = NULL;

	dnode_rele(zv->zv_dn, FTAG);
	zv->zv_dn = NULL;

	/*
	 * Evict cached data. We must write out any dirty data before
	 * disowning the dataset.
	 */
	if (zv->zv_flags & ZVOL_WRITTEN_TO)
		txg_wait_synced(dmu_objset_pool(zv->zv_objset), 0);
	(void) dmu_objset_evict_dbufs(zv->zv_objset);
}