#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sio_nr_dvas; int /*<<< orphan*/ * sio_dva; int /*<<< orphan*/  sio_cksum; int /*<<< orphan*/  sio_birth; int /*<<< orphan*/  sio_phys_birth; int /*<<< orphan*/  sio_blk_prop; } ;
typedef  TYPE_1__ scan_io_t ;
struct TYPE_7__ {int /*<<< orphan*/ * blk_dva; int /*<<< orphan*/  blk_cksum; int /*<<< orphan*/  blk_birth; int /*<<< orphan*/  blk_phys_birth; int /*<<< orphan*/  blk_prop; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int BP_GET_NDVAS (TYPE_2__ const*) ; 

__attribute__((used)) static inline void
bp2sio(const blkptr_t *bp, scan_io_t *sio, int dva_i)
{
	sio->sio_blk_prop = bp->blk_prop;
	sio->sio_phys_birth = bp->blk_phys_birth;
	sio->sio_birth = bp->blk_birth;
	sio->sio_cksum = bp->blk_cksum;
	sio->sio_nr_dvas = BP_GET_NDVAS(bp);

	/*
	 * Copy the DVAs to the sio. We need all copies of the block so
	 * that the self healing code can use the alternate copies if the
	 * first is corrupted. We want the DVA at index dva_i to be first
	 * in the sio since this is the primary one that we want to issue.
	 */
	for (int i = 0, j = dva_i; i < sio->sio_nr_dvas; i++, j++) {
		sio->sio_dva[i] = bp->blk_dva[j % sio->sio_nr_dvas];
	}
}