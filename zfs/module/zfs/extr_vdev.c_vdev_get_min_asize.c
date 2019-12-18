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
struct TYPE_3__ {int vdev_asize; unsigned long long vdev_ms_shift; int vdev_min_asize; int vdev_children; int /*<<< orphan*/ * vdev_ops; struct TYPE_3__* vdev_top; struct TYPE_3__* vdev_parent; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int P2ALIGN (int,unsigned long long) ; 
 int /*<<< orphan*/  vdev_raidz_ops ; 

uint64_t
vdev_get_min_asize(vdev_t *vd)
{
	vdev_t *pvd = vd->vdev_parent;

	/*
	 * If our parent is NULL (inactive spare or cache) or is the root,
	 * just return our own asize.
	 */
	if (pvd == NULL)
		return (vd->vdev_asize);

	/*
	 * The top-level vdev just returns the allocatable size rounded
	 * to the nearest metaslab.
	 */
	if (vd == vd->vdev_top)
		return (P2ALIGN(vd->vdev_asize, 1ULL << vd->vdev_ms_shift));

	/*
	 * The allocatable space for a raidz vdev is N * sizeof(smallest child),
	 * so each child must provide at least 1/Nth of its asize.
	 */
	if (pvd->vdev_ops == &vdev_raidz_ops)
		return ((pvd->vdev_min_asize + pvd->vdev_children - 1) /
		    pvd->vdev_children);

	return (pvd->vdev_min_asize);
}