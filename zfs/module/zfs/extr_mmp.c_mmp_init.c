#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mmp_kstat_id; int /*<<< orphan*/  mmp_delay; int /*<<< orphan*/  mmp_last_write; int /*<<< orphan*/  mmp_io_lock; int /*<<< orphan*/  mmp_thread_cv; int /*<<< orphan*/  mmp_thread_lock; } ;
struct TYPE_4__ {TYPE_2__ spa_mmp; } ;
typedef  TYPE_1__ spa_t ;
typedef  TYPE_2__ mmp_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MMP_INTERVAL_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_multihost_interval ; 

void
mmp_init(spa_t *spa)
{
	mmp_thread_t *mmp = &spa->spa_mmp;

	mutex_init(&mmp->mmp_thread_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&mmp->mmp_thread_cv, NULL, CV_DEFAULT, NULL);
	mutex_init(&mmp->mmp_io_lock, NULL, MUTEX_DEFAULT, NULL);
	mmp->mmp_kstat_id = 1;

	/*
	 * mmp_write_done() calculates mmp_delay based on prior mmp_delay and
	 * the elapsed time since the last write.  For the first mmp write,
	 * there is no "last write", so we start with fake non-zero values.
	 */
	mmp->mmp_last_write = gethrtime();
	mmp->mmp_delay = MSEC2NSEC(MMP_INTERVAL_OK(zfs_multihost_interval));
}