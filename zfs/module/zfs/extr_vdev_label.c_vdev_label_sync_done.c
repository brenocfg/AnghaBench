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
struct TYPE_3__ {scalar_t__ io_error; int /*<<< orphan*/ * io_private; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_label_sync_done(zio_t *zio)
{
	uint64_t *good_writes = zio->io_private;

	if (zio->io_error == 0)
		atomic_inc_64(good_writes);
}