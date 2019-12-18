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
struct TYPE_4__ {int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  raidz_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  raidz_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vdev_raidz_map_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fini_raidz_map(zio_t **zio, raidz_map_t **rm)
{
	vdev_raidz_map_free(*rm);
	raidz_free((*zio)->io_abd, (*zio)->io_size);
	umem_free(*zio, sizeof (zio_t));

	*zio = NULL;
	*rm = NULL;
}