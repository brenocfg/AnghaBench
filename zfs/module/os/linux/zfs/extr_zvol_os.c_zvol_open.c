#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zv_open_count; int zv_flags; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_state_lock; } ;
typedef  TYPE_2__ zvol_state_t ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int fmode_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {TYPE_2__* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int EINTR ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int ZVOL_RDONLY ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_tryenter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int zvol_first_open (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zvol_last_close (TYPE_2__*) ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static int
zvol_open(struct block_device *bdev, fmode_t flag)
{
	zvol_state_t *zv;
	int error = 0;
	boolean_t drop_suspend = B_TRUE;

	rw_enter(&zvol_state_lock, RW_READER);
	/*
	 * Obtain a copy of private_data under the zvol_state_lock to make
	 * sure that either the result of zvol free code path setting
	 * bdev->bd_disk->private_data to NULL is observed, or zvol_free()
	 * is not called on this zv because of the positive zv_open_count.
	 */
	zv = bdev->bd_disk->private_data;
	if (zv == NULL) {
		rw_exit(&zvol_state_lock);
		return (SET_ERROR(-ENXIO));
	}

	mutex_enter(&zv->zv_state_lock);
	/*
	 * make sure zvol is not suspended during first open
	 * (hold zv_suspend_lock) and respect proper lock acquisition
	 * ordering - zv_suspend_lock before zv_state_lock
	 */
	if (zv->zv_open_count == 0) {
		if (!rw_tryenter(&zv->zv_suspend_lock, RW_READER)) {
			mutex_exit(&zv->zv_state_lock);
			rw_enter(&zv->zv_suspend_lock, RW_READER);
			mutex_enter(&zv->zv_state_lock);
			/* check to see if zv_suspend_lock is needed */
			if (zv->zv_open_count != 0) {
				rw_exit(&zv->zv_suspend_lock);
				drop_suspend = B_FALSE;
			}
		}
	} else {
		drop_suspend = B_FALSE;
	}
	rw_exit(&zvol_state_lock);

	ASSERT(MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(zv->zv_open_count != 0 || RW_READ_HELD(&zv->zv_suspend_lock));

	if (zv->zv_open_count == 0) {
		error = -zvol_first_open(zv, !(flag & FMODE_WRITE));
		if (error)
			goto out_mutex;
	}

	if ((flag & FMODE_WRITE) && (zv->zv_flags & ZVOL_RDONLY)) {
		error = -EROFS;
		goto out_open_count;
	}

	zv->zv_open_count++;

	mutex_exit(&zv->zv_state_lock);
	if (drop_suspend)
		rw_exit(&zv->zv_suspend_lock);

	check_disk_change(bdev);

	return (0);

out_open_count:
	if (zv->zv_open_count == 0)
		zvol_last_close(zv);

out_mutex:
	mutex_exit(&zv->zv_state_lock);
	if (drop_suspend)
		rw_exit(&zv->zv_suspend_lock);
	if (error == -EINTR) {
		error = -ERESTARTSYS;
		schedule();
	}
	return (SET_ERROR(error));
}