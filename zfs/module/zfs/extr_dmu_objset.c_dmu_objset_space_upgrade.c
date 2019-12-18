#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  os_upgrade_lock; scalar_t__ os_upgrade_exit; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int dmu_bonus_hold (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_object_next (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmu_objset_space_upgrade(objset_t *os)
{
	uint64_t obj;
	int err = 0;

	/*
	 * We simply need to mark every object dirty, so that it will be
	 * synced out and now accounted.  If this is called
	 * concurrently, or if we already did some work before crashing,
	 * that's fine, since we track each object's accounted state
	 * independently.
	 */

	for (obj = 0; err == 0; err = dmu_object_next(os, &obj, FALSE, 0)) {
		dmu_tx_t *tx;
		dmu_buf_t *db;
		int objerr;

		mutex_enter(&os->os_upgrade_lock);
		if (os->os_upgrade_exit)
			err = SET_ERROR(EINTR);
		mutex_exit(&os->os_upgrade_lock);
		if (err != 0)
			return (err);

		if (issig(JUSTLOOKING) && issig(FORREAL))
			return (SET_ERROR(EINTR));

		objerr = dmu_bonus_hold(os, obj, FTAG, &db);
		if (objerr != 0)
			continue;
		tx = dmu_tx_create(os);
		dmu_tx_hold_bonus(tx, obj);
		objerr = dmu_tx_assign(tx, TXG_WAIT);
		if (objerr != 0) {
			dmu_buf_rele(db, FTAG);
			dmu_tx_abort(tx);
			continue;
		}
		dmu_buf_will_dirty(db, tx);
		dmu_buf_rele(db, FTAG);
		dmu_tx_commit(tx);
	}
	return (0);
}