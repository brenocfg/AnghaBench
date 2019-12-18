#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  scn_visited_this_txg; TYPE_2__* scn_dp; int /*<<< orphan*/  scn_zio_root; int /*<<< orphan*/  scn_is_bptree; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_12__ {TYPE_1__* tx_pool; } ;
typedef  TYPE_4__ dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_spa; } ;
struct TYPE_9__ {int /*<<< orphan*/  dp_free_dir; } ;

/* Variables and functions */
 scalar_t__ BP_GET_LEVEL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_TYPE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_UCSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DD_USED_HEAD ; 
 scalar_t__ DMU_OT_OBJSET ; 
 int /*<<< orphan*/  ERESTART ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp_get_dsize_sync (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ dsl_scan_async_block_should_pause (TYPE_3__*) ; 
 int /*<<< orphan*/  zio_free_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_scan_free_block_cb(void *arg, const blkptr_t *bp, dmu_tx_t *tx)
{
	dsl_scan_t *scn = arg;

	if (!scn->scn_is_bptree ||
	    (BP_GET_LEVEL(bp) == 0 && BP_GET_TYPE(bp) != DMU_OT_OBJSET)) {
		if (dsl_scan_async_block_should_pause(scn))
			return (SET_ERROR(ERESTART));
	}

	zio_nowait(zio_free_sync(scn->scn_zio_root, scn->scn_dp->dp_spa,
	    dmu_tx_get_txg(tx), bp, 0));
	dsl_dir_diduse_space(tx->tx_pool->dp_free_dir, DD_USED_HEAD,
	    -bp_get_dsize_sync(scn->scn_dp->dp_spa, bp),
	    -BP_GET_PSIZE(bp), -BP_GET_UCSIZE(bp), tx);
	scn->scn_visited_this_txg++;
	return (0);
}