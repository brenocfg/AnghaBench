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
struct TYPE_6__ {size_t vdev_children; size_t vdev_nparity; struct TYPE_6__** vdev_child; TYPE_1__* vdev_top; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {size_t vdev_ashift; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DTL_PARTIAL ; 
 int /*<<< orphan*/  vdev_dtl_empty (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
vdev_raidz_need_resilver(vdev_t *vd, uint64_t offset, size_t psize)
{
	uint64_t dcols = vd->vdev_children;
	uint64_t nparity = vd->vdev_nparity;
	uint64_t ashift = vd->vdev_top->vdev_ashift;
	/* The starting RAIDZ (parent) vdev sector of the block. */
	uint64_t b = offset >> ashift;
	/* The zio's size in units of the vdev's minimum sector size. */
	uint64_t s = ((psize - 1) >> ashift) + 1;
	/* The first column for this stripe. */
	uint64_t f = b % dcols;

	if (s + nparity >= dcols)
		return (B_TRUE);

	for (uint64_t c = 0; c < s + nparity; c++) {
		uint64_t devidx = (f + c) % dcols;
		vdev_t *cvd = vd->vdev_child[devidx];

		/*
		 * dsl_scan_need_resilver() already checked vd with
		 * vdev_dtl_contains(). So here just check cvd with
		 * vdev_dtl_empty(), cheaper and a good approximation.
		 */
		if (!vdev_dtl_empty(cvd, DTL_PARTIAL))
			return (B_TRUE);
	}

	return (B_FALSE);
}