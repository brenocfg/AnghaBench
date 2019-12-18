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
struct TYPE_6__ {int /*<<< orphan*/  mm_children; } ;
typedef  TYPE_2__ mirror_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_mirror_map_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_mirror_map_free(zio_t *zio)
{
	mirror_map_t *mm = zio->io_vsd;

	kmem_free(mm, vdev_mirror_map_size(mm->mm_children));
}