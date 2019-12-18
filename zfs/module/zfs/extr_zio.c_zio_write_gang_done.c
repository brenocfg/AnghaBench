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
struct TYPE_3__ {int /*<<< orphan*/ * io_abd; } ;
typedef  TYPE_1__ zio_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zio_write_gang_done(zio_t *zio)
{
	/*
	 * The io_abd field will be NULL for a zio with no data.  The io_flags
	 * will initially have the ZIO_FLAG_NODATA bit flag set, but we can't
	 * check for it here as it is cleared in zio_ready.
	 */
	if (zio->io_abd != NULL)
		abd_put(zio->io_abd);
}