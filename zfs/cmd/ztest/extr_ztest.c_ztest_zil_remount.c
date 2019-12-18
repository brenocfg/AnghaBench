#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zd_zilog; int /*<<< orphan*/  zd_dirobj_lock; int /*<<< orphan*/  zd_zilog_lock; int /*<<< orphan*/ * zd_os; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_close (scalar_t__) ; 
 scalar_t__ zil_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_replay (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_get_data ; 
 int /*<<< orphan*/  ztest_replay_vector ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_zil_remount(ztest_ds_t *zd, uint64_t id)
{
	objset_t *os = zd->zd_os;

	/*
	 * We hold the ztest_vdev_lock so we don't cause problems with
	 * other threads that wish to remove a log device, such as
	 * ztest_device_removal().
	 */
	mutex_enter(&ztest_vdev_lock);

	/*
	 * We grab the zd_dirobj_lock to ensure that no other thread is
	 * updating the zil (i.e. adding in-memory log records) and the
	 * zd_zilog_lock to block any I/O.
	 */
	mutex_enter(&zd->zd_dirobj_lock);
	(void) pthread_rwlock_wrlock(&zd->zd_zilog_lock);

	/* zfsvfs_teardown() */
	zil_close(zd->zd_zilog);

	/* zfsvfs_setup() */
	VERIFY(zil_open(os, ztest_get_data) == zd->zd_zilog);
	zil_replay(os, zd, ztest_replay_vector);

	(void) pthread_rwlock_unlock(&zd->zd_zilog_lock);
	mutex_exit(&zd->zd_dirobj_lock);
	mutex_exit(&ztest_vdev_lock);
}