#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_7__ {int /*<<< orphan*/  scn_visited_this_txg; TYPE_1__* scn_dp; } ;
typedef  TYPE_2__ dsl_scan_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_3__ blkptr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DVA_GET_ASIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERESTART ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_scan_async_block_should_pause (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_vdev_indirect_mark_obsolete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_scan_obsolete_block_cb(void *arg, const blkptr_t *bp, boolean_t bp_freed,
    dmu_tx_t *tx)
{
	ASSERT(!bp_freed);
	dsl_scan_t *scn = arg;
	const dva_t *dva = &bp->blk_dva[0];

	if (dsl_scan_async_block_should_pause(scn))
		return (SET_ERROR(ERESTART));

	spa_vdev_indirect_mark_obsolete(scn->scn_dp->dp_spa,
	    DVA_GET_VDEV(dva), DVA_GET_OFFSET(dva),
	    DVA_GET_ASIZE(dva), tx);
	scn->scn_visited_this_txg++;
	return (0);
}