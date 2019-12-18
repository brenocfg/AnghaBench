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
struct TYPE_4__ {scalar_t__ io_error; scalar_t__ io_size; int /*<<< orphan*/  io_abd; TYPE_2__* io_private; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_5__ {int /*<<< orphan*/  vca_lock; int /*<<< orphan*/  vca_cv; int /*<<< orphan*/  vca_write_error_bytes; int /*<<< orphan*/  vca_outstanding_bytes; } ;
typedef  TYPE_2__ vdev_copy_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_vdev_copy_segment_write_done(zio_t *zio)
{
	vdev_copy_arg_t *vca = zio->io_private;

	abd_free(zio->io_abd);

	mutex_enter(&vca->vca_lock);
	vca->vca_outstanding_bytes -= zio->io_size;

	if (zio->io_error != 0)
		vca->vca_write_error_bytes += zio->io_size;

	cv_signal(&vca->vca_cv);
	mutex_exit(&vca->vca_lock);
}