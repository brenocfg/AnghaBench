#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_8__ {int /*<<< orphan*/  b_refcnt; } ;
struct TYPE_9__ {TYPE_1__ b_l1hdr; } ;
typedef  TYPE_2__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HDR_HAS_L1HDR (TYPE_2__*) ; 
 int /*<<< orphan*/  HDR_IO_IN_PROGRESS (TYPE_2__*) ; 
 int /*<<< orphan*/  arc_anon ; 
 int /*<<< orphan*/  arc_change_state (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_hdr_destroy (TYPE_2__*) ; 
 TYPE_2__* buf_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_load_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

void
arc_freed(spa_t *spa, const blkptr_t *bp)
{
	arc_buf_hdr_t *hdr;
	kmutex_t *hash_lock;
	uint64_t guid = spa_load_guid(spa);

	ASSERT(!BP_IS_EMBEDDED(bp));

	hdr = buf_hash_find(guid, bp, &hash_lock);
	if (hdr == NULL)
		return;

	/*
	 * We might be trying to free a block that is still doing I/O
	 * (i.e. prefetch) or has a reference (i.e. a dedup-ed,
	 * dmu_sync-ed block). If this block is being prefetched, then it
	 * would still have the ARC_FLAG_IO_IN_PROGRESS flag set on the hdr
	 * until the I/O completes. A block may also have a reference if it is
	 * part of a dedup-ed, dmu_synced write. The dmu_sync() function would
	 * have written the new block to its final resting place on disk but
	 * without the dedup flag set. This would have left the hdr in the MRU
	 * state and discoverable. When the txg finally syncs it detects that
	 * the block was overridden in open context and issues an override I/O.
	 * Since this is a dedup block, the override I/O will determine if the
	 * block is already in the DDT. If so, then it will replace the io_bp
	 * with the bp from the DDT and allow the I/O to finish. When the I/O
	 * reaches the done callback, dbuf_write_override_done, it will
	 * check to see if the io_bp and io_bp_override are identical.
	 * If they are not, then it indicates that the bp was replaced with
	 * the bp in the DDT and the override bp is freed. This allows
	 * us to arrive here with a reference on a block that is being
	 * freed. So if we have an I/O in progress, or a reference to
	 * this hdr, then we don't destroy the hdr.
	 */
	if (!HDR_HAS_L1HDR(hdr) || (!HDR_IO_IN_PROGRESS(hdr) &&
	    zfs_refcount_is_zero(&hdr->b_l1hdr.b_refcnt))) {
		arc_change_state(arc_anon, hdr, hash_lock);
		arc_hdr_destroy(hdr);
		mutex_exit(hash_lock);
	} else {
		mutex_exit(hash_lock);
	}

}