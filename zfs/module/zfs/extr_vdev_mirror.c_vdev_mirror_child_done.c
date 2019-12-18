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
struct TYPE_5__ {int mc_tried; scalar_t__ mc_skipped; int /*<<< orphan*/  mc_error; } ;
typedef  TYPE_2__ mirror_child_t ;

/* Variables and functions */

__attribute__((used)) static void
vdev_mirror_child_done(zio_t *zio)
{
	mirror_child_t *mc = zio->io_private;

	mc->mc_error = zio->io_error;
	mc->mc_tried = 1;
	mc->mc_skipped = 0;
}