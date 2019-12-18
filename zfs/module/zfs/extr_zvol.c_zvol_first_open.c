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
struct TYPE_6__ {int /*<<< orphan*/ * zv_objset; int /*<<< orphan*/  zv_name; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_suspend_lock; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZVOL ; 
 int EINTR ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int dmu_objset_own (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_owned (int /*<<< orphan*/ *) ; 
 int mutex_tryenter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int zvol_setup_zv (TYPE_1__*) ; 

int
zvol_first_open(zvol_state_t *zv, boolean_t readonly)
{
	objset_t *os;
	int error, locked = 0;
	boolean_t ro;

	ASSERT(RW_READ_HELD(&zv->zv_suspend_lock));
	ASSERT(MUTEX_HELD(&zv->zv_state_lock));

	/*
	 * In all other cases the spa_namespace_lock is taken before the
	 * bdev->bd_mutex lock.	 But in this case the Linux __blkdev_get()
	 * function calls fops->open() with the bdev->bd_mutex lock held.
	 * This deadlock can be easily observed with zvols used as vdevs.
	 *
	 * To avoid a potential lock inversion deadlock we preemptively
	 * try to take the spa_namespace_lock().  Normally it will not
	 * be contended and this is safe because spa_open_common() handles
	 * the case where the caller already holds the spa_namespace_lock.
	 *
	 * When it is contended we risk a lock inversion if we were to
	 * block waiting for the lock.	Luckily, the __blkdev_get()
	 * function allows us to return -ERESTARTSYS which will result in
	 * bdev->bd_mutex being dropped, reacquired, and fops->open() being
	 * called again.  This process can be repeated safely until both
	 * locks are acquired.
	 */
	if (!mutex_owned(&spa_namespace_lock)) {
		locked = mutex_tryenter(&spa_namespace_lock);
		if (!locked)
			return (SET_ERROR(EINTR));
	}

	ro = (readonly || (strchr(zv->zv_name, '@') != NULL));
	error = dmu_objset_own(zv->zv_name, DMU_OST_ZVOL, ro, B_TRUE, zv, &os);
	if (error)
		goto out_mutex;

	zv->zv_objset = os;

	error = zvol_setup_zv(zv);

	if (error) {
		dmu_objset_disown(os, 1, zv);
		zv->zv_objset = NULL;
	}

out_mutex:
	if (locked)
		mutex_exit(&spa_namespace_lock);
	return (SET_ERROR(error));
}