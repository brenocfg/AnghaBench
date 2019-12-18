#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct space_range_arg {scalar_t__ mintxg; scalar_t__ maxtxg; int /*<<< orphan*/  uncomp; int /*<<< orphan*/  comp; int /*<<< orphan*/  spa; int /*<<< orphan*/  used; } ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {scalar_t__ blk_birth; } ;
typedef  TYPE_1__ blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_GET_PSIZE (TYPE_1__ const*) ; 
 scalar_t__ BP_GET_UCSIZE (TYPE_1__ const*) ; 
 scalar_t__ bp_get_dsize (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 scalar_t__ bp_get_dsize_sync (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 scalar_t__ dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
space_range_cb(void *arg, const blkptr_t *bp, boolean_t bp_freed, dmu_tx_t *tx)
{
	struct space_range_arg *sra = arg;

	if (bp->blk_birth > sra->mintxg && bp->blk_birth <= sra->maxtxg) {
		if (dsl_pool_sync_context(spa_get_dsl(sra->spa)))
			sra->used += bp_get_dsize_sync(sra->spa, bp);
		else
			sra->used += bp_get_dsize(sra->spa, bp);
		sra->comp += BP_GET_PSIZE(bp);
		sra->uncomp += BP_GET_UCSIZE(bp);
	}
	return (0);
}