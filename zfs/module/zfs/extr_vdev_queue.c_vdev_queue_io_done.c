#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* io_timestamp; scalar_t__ io_done; void* io_delta; TYPE_1__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_14__ {void* vq_io_complete_ts; void* vq_io_delta_ts; int /*<<< orphan*/  vq_lock; } ;
typedef  TYPE_3__ vdev_queue_t ;
struct TYPE_12__ {TYPE_3__ vdev_queue; } ;

/* Variables and functions */
 void* gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_queue_agg_io_done ; 
 TYPE_2__* vdev_queue_io_to_issue (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_queue_pending_remove (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_execute (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_vdev_io_reissue (TYPE_2__*) ; 

void
vdev_queue_io_done(zio_t *zio)
{
	vdev_queue_t *vq = &zio->io_vd->vdev_queue;
	zio_t *nio;

	mutex_enter(&vq->vq_lock);

	vdev_queue_pending_remove(vq, zio);

	zio->io_delta = gethrtime() - zio->io_timestamp;
	vq->vq_io_complete_ts = gethrtime();
	vq->vq_io_delta_ts = vq->vq_io_complete_ts - zio->io_timestamp;

	while ((nio = vdev_queue_io_to_issue(vq)) != NULL) {
		mutex_exit(&vq->vq_lock);
		if (nio->io_done == vdev_queue_agg_io_done) {
			zio_nowait(nio);
		} else {
			zio_vdev_io_reissue(nio);
			zio_execute(nio);
		}
		mutex_enter(&vq->vq_lock);
	}

	mutex_exit(&vq->vq_lock);
}