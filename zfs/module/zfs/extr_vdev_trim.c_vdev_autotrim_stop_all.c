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
struct TYPE_4__ {size_t vdev_children; int /*<<< orphan*/ * vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_5__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_autotrim_stop_wait (int /*<<< orphan*/ ) ; 

void
vdev_autotrim_stop_all(spa_t *spa)
{
	vdev_t *root_vd = spa->spa_root_vdev;

	for (uint64_t i = 0; i < root_vd->vdev_children; i++)
		vdev_autotrim_stop_wait(root_vd->vdev_child[i]);
}