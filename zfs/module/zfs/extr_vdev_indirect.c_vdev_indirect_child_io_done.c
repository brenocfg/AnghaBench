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
struct TYPE_3__ {int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_error; struct TYPE_3__* io_private; } ;
typedef  TYPE_1__ zio_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_worst_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_indirect_child_io_done(zio_t *zio)
{
	zio_t *pio = zio->io_private;

	mutex_enter(&pio->io_lock);
	pio->io_error = zio_worst_error(pio->io_error, zio->io_error);
	mutex_exit(&pio->io_lock);

	abd_put(zio->io_abd);
}