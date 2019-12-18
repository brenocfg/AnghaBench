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
struct TYPE_3__ {int zv_open_count; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_state_lock; } ;
typedef  TYPE_1__ zvol_state_t ;
struct gendisk {TYPE_1__* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_tryenter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_last_close (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static void
zvol_release(struct gendisk *disk, fmode_t mode)
{
	zvol_state_t *zv;
	boolean_t drop_suspend = B_TRUE;

	rw_enter(&zvol_state_lock, RW_READER);
	zv = disk->private_data;

	mutex_enter(&zv->zv_state_lock);
	ASSERT(zv->zv_open_count > 0);
	/*
	 * make sure zvol is not suspended during last close
	 * (hold zv_suspend_lock) and respect proper lock acquisition
	 * ordering - zv_suspend_lock before zv_state_lock
	 */
	if (zv->zv_open_count == 1) {
		if (!rw_tryenter(&zv->zv_suspend_lock, RW_READER)) {
			mutex_exit(&zv->zv_state_lock);
			rw_enter(&zv->zv_suspend_lock, RW_READER);
			mutex_enter(&zv->zv_state_lock);
			/* check to see if zv_suspend_lock is needed */
			if (zv->zv_open_count != 1) {
				rw_exit(&zv->zv_suspend_lock);
				drop_suspend = B_FALSE;
			}
		}
	} else {
		drop_suspend = B_FALSE;
	}
	rw_exit(&zvol_state_lock);

	ASSERT(MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(zv->zv_open_count != 1 || RW_READ_HELD(&zv->zv_suspend_lock));

	zv->zv_open_count--;
	if (zv->zv_open_count == 0)
		zvol_last_close(zv);

	mutex_exit(&zv->zv_state_lock);

	if (drop_suspend)
		rw_exit(&zv->zv_suspend_lock);
}