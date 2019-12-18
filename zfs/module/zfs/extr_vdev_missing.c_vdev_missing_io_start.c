#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_error; } ;
typedef  TYPE_1__ zio_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_execute (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_missing_io_start(zio_t *zio)
{
	zio->io_error = SET_ERROR(ENOTSUP);
	zio_execute(zio);
}