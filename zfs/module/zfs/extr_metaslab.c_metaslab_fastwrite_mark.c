#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vdev_pending_fastwrite; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_10__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_GET_NDVAS (TYPE_2__ const*) ; 
 scalar_t__ BP_GET_PSIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BP_IS_HOLE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vdev_lookup_top (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
metaslab_fastwrite_mark(spa_t *spa, const blkptr_t *bp)
{
	const dva_t *dva = bp->blk_dva;
	int ndvas = BP_GET_NDVAS(bp);
	uint64_t psize = BP_GET_PSIZE(bp);
	int d;
	vdev_t *vd;

	ASSERT(!BP_IS_HOLE(bp));
	ASSERT(!BP_IS_EMBEDDED(bp));
	ASSERT(psize > 0);

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	for (d = 0; d < ndvas; d++) {
		if ((vd = vdev_lookup_top(spa, DVA_GET_VDEV(&dva[d]))) == NULL)
			continue;
		atomic_add_64(&vd->vdev_pending_fastwrite, psize);
	}

	spa_config_exit(spa, SCL_VDEV, FTAG);
}