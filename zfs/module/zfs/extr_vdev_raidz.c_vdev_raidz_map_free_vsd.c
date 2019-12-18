#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {int rm_freed; scalar_t__ rm_reports; } ;
typedef  TYPE_2__ raidz_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  vdev_raidz_map_free (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_raidz_map_free_vsd(zio_t *zio)
{
	raidz_map_t *rm = zio->io_vsd;

	ASSERT0(rm->rm_freed);
	rm->rm_freed = 1;

	if (rm->rm_reports == 0)
		vdev_raidz_map_free(rm);
}