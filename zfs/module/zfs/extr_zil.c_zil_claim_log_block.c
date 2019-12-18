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
struct TYPE_9__ {int /*<<< orphan*/  zl_spa; } ;
typedef  TYPE_1__ zilog_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ blk_birth; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_IS_HOLE (TYPE_2__*) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_SCRUB ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  spa_claim_notify ; 
 scalar_t__ zil_bp_tree_add (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_claim (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int zio_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zil_claim_log_block(zilog_t *zilog, blkptr_t *bp, void *tx, uint64_t first_txg)
{
	/*
	 * Claim log block if not already committed and not already claimed.
	 * If tx == NULL, just verify that the block is claimable.
	 */
	if (BP_IS_HOLE(bp) || bp->blk_birth < first_txg ||
	    zil_bp_tree_add(zilog, bp) != 0)
		return (0);

	return (zio_wait(zio_claim(NULL, zilog->zl_spa,
	    tx == NULL ? 0 : first_txg, bp, spa_claim_notify, NULL,
	    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE | ZIO_FLAG_SCRUB)));
}