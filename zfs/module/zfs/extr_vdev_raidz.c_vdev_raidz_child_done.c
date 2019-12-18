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
struct TYPE_4__ {int /*<<< orphan*/  io_error; TYPE_2__* io_private; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_5__ {int rc_tried; scalar_t__ rc_skipped; int /*<<< orphan*/  rc_error; } ;
typedef  TYPE_2__ raidz_col_t ;

/* Variables and functions */

__attribute__((used)) static void
vdev_raidz_child_done(zio_t *zio)
{
	raidz_col_t *rc = zio->io_private;

	rc->rc_error = zio->io_error;
	rc->rc_tried = 1;
	rc->rc_skipped = 0;
}