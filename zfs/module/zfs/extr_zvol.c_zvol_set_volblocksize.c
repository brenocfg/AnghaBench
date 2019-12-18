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
struct TYPE_3__ {int zv_flags; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_volblocksize; int /*<<< orphan*/  zv_objset; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOTSUP ; 
 int ENXIO ; 
 int EROFS ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int ZVOL_RDONLY ; 
 int dmu_object_set_blocksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* zvol_find_by_name (char const*,int /*<<< orphan*/ ) ; 

int
zvol_set_volblocksize(const char *name, uint64_t volblocksize)
{
	zvol_state_t *zv;
	dmu_tx_t *tx;
	int error;

	zv = zvol_find_by_name(name, RW_READER);

	if (zv == NULL)
		return (SET_ERROR(ENXIO));

	ASSERT(MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(RW_READ_HELD(&zv->zv_suspend_lock));

	if (zv->zv_flags & ZVOL_RDONLY) {
		mutex_exit(&zv->zv_state_lock);
		rw_exit(&zv->zv_suspend_lock);
		return (SET_ERROR(EROFS));
	}

	tx = dmu_tx_create(zv->zv_objset);
	dmu_tx_hold_bonus(tx, ZVOL_OBJ);
	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error) {
		dmu_tx_abort(tx);
	} else {
		error = dmu_object_set_blocksize(zv->zv_objset, ZVOL_OBJ,
		    volblocksize, 0, tx);
		if (error == ENOTSUP)
			error = SET_ERROR(EBUSY);
		dmu_tx_commit(tx);
		if (error == 0)
			zv->zv_volblocksize = volblocksize;
	}

	mutex_exit(&zv->zv_state_lock);
	rw_exit(&zv->zv_suspend_lock);

	return (SET_ERROR(error));
}