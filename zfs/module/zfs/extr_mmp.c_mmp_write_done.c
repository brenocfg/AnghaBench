#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ io_error; int /*<<< orphan*/  io_abd; TYPE_3__* io_private; TYPE_2__* io_vd; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {scalar_t__ vdev_mmp_kstat_id; scalar_t__ vdev_mmp_pending; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  mmp_io_lock; } ;
typedef  TYPE_3__ mmp_thread_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  mmp_delay_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmp_tag ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_mmp_history_set (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mmp_write_done(zio_t *zio)
{
	spa_t *spa = zio->io_spa;
	vdev_t *vd = zio->io_vd;
	mmp_thread_t *mts = zio->io_private;

	mutex_enter(&mts->mmp_io_lock);
	uint64_t mmp_kstat_id = vd->vdev_mmp_kstat_id;
	hrtime_t mmp_write_duration = gethrtime() - vd->vdev_mmp_pending;

	mmp_delay_update(spa, (zio->io_error == 0));

	vd->vdev_mmp_pending = 0;
	vd->vdev_mmp_kstat_id = 0;

	mutex_exit(&mts->mmp_io_lock);
	spa_config_exit(spa, SCL_STATE, mmp_tag);

	spa_mmp_history_set(spa, mmp_kstat_id, zio->io_error,
	    mmp_write_duration);

	abd_free(zio->io_abd);
}