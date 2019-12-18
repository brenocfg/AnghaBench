#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int io_flags; scalar_t__ io_type; scalar_t__ io_priority; scalar_t__ io_done; int /*<<< orphan*/  io_timestamp; TYPE_1__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_13__ {int /*<<< orphan*/  vq_lock; } ;
typedef  TYPE_3__ vdev_queue_t ;
struct TYPE_11__ {TYPE_3__ vdev_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ZIO_FLAG_DONT_CACHE ; 
 int ZIO_FLAG_DONT_QUEUE ; 
 scalar_t__ ZIO_PRIORITY_ASYNC_READ ; 
 scalar_t__ ZIO_PRIORITY_ASYNC_WRITE ; 
 scalar_t__ ZIO_PRIORITY_INITIALIZING ; 
 scalar_t__ ZIO_PRIORITY_REMOVAL ; 
 scalar_t__ ZIO_PRIORITY_SCRUB ; 
 scalar_t__ ZIO_PRIORITY_SYNC_READ ; 
 scalar_t__ ZIO_PRIORITY_SYNC_WRITE ; 
 scalar_t__ ZIO_PRIORITY_TRIM ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_TRIM ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_queue_agg_io_done ; 
 int /*<<< orphan*/  vdev_queue_io_add (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* vdev_queue_io_to_issue (TYPE_3__*) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_2__*) ; 

zio_t *
vdev_queue_io(zio_t *zio)
{
	vdev_queue_t *vq = &zio->io_vd->vdev_queue;
	zio_t *nio;

	if (zio->io_flags & ZIO_FLAG_DONT_QUEUE)
		return (zio);

	/*
	 * Children i/os inherent their parent's priority, which might
	 * not match the child's i/o type.  Fix it up here.
	 */
	if (zio->io_type == ZIO_TYPE_READ) {
		ASSERT(zio->io_priority != ZIO_PRIORITY_TRIM);

		if (zio->io_priority != ZIO_PRIORITY_SYNC_READ &&
		    zio->io_priority != ZIO_PRIORITY_ASYNC_READ &&
		    zio->io_priority != ZIO_PRIORITY_SCRUB &&
		    zio->io_priority != ZIO_PRIORITY_REMOVAL &&
		    zio->io_priority != ZIO_PRIORITY_INITIALIZING) {
			zio->io_priority = ZIO_PRIORITY_ASYNC_READ;
		}
	} else if (zio->io_type == ZIO_TYPE_WRITE) {
		ASSERT(zio->io_priority != ZIO_PRIORITY_TRIM);

		if (zio->io_priority != ZIO_PRIORITY_SYNC_WRITE &&
		    zio->io_priority != ZIO_PRIORITY_ASYNC_WRITE &&
		    zio->io_priority != ZIO_PRIORITY_REMOVAL &&
		    zio->io_priority != ZIO_PRIORITY_INITIALIZING) {
			zio->io_priority = ZIO_PRIORITY_ASYNC_WRITE;
		}
	} else {
		ASSERT(zio->io_type == ZIO_TYPE_TRIM);
		ASSERT(zio->io_priority == ZIO_PRIORITY_TRIM);
	}

	zio->io_flags |= ZIO_FLAG_DONT_CACHE | ZIO_FLAG_DONT_QUEUE;

	mutex_enter(&vq->vq_lock);
	zio->io_timestamp = gethrtime();
	vdev_queue_io_add(vq, zio);
	nio = vdev_queue_io_to_issue(vq);
	mutex_exit(&vq->vq_lock);

	if (nio == NULL)
		return (NULL);

	if (nio->io_done == vdev_queue_agg_io_done) {
		zio_nowait(nio);
		return (NULL);
	}

	return (nio);
}