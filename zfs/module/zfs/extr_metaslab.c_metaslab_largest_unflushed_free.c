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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
struct TYPE_3__ {int /*<<< orphan*/  ms_freed; int /*<<< orphan*/ * ms_defer; int /*<<< orphan*/ * ms_unflushed_frees; int /*<<< orphan*/  ms_unflushed_frees_by_size; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  metaslab_size_tree_full_load (int /*<<< orphan*/ *) ; 
 scalar_t__ range_tree_find_in (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ rs_get_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rs_get_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_btree_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_btree_numnodes (int /*<<< orphan*/ *) ; 

uint64_t
metaslab_largest_unflushed_free(metaslab_t *msp)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	if (msp->ms_unflushed_frees == NULL)
		return (0);

	if (zfs_btree_numnodes(&msp->ms_unflushed_frees_by_size) == 0)
		metaslab_size_tree_full_load(msp->ms_unflushed_frees);
	range_seg_t *rs = zfs_btree_last(&msp->ms_unflushed_frees_by_size,
	    NULL);
	if (rs == NULL)
		return (0);

	/*
	 * When a range is freed from the metaslab, that range is added to
	 * both the unflushed frees and the deferred frees. While the block
	 * will eventually be usable, if the metaslab were loaded the range
	 * would not be added to the ms_allocatable tree until TXG_DEFER_SIZE
	 * txgs had passed.  As a result, when attempting to estimate an upper
	 * bound for the largest currently-usable free segment in the
	 * metaslab, we need to not consider any ranges currently in the defer
	 * trees. This algorithm approximates the largest available chunk in
	 * the largest range in the unflushed_frees tree by taking the first
	 * chunk.  While this may be a poor estimate, it should only remain so
	 * briefly and should eventually self-correct as frees are no longer
	 * deferred. Similar logic applies to the ms_freed tree. See
	 * metaslab_load() for more details.
	 *
	 * There are two primary sources of inaccuracy in this estimate. Both
	 * are tolerated for performance reasons. The first source is that we
	 * only check the largest segment for overlaps. Smaller segments may
	 * have more favorable overlaps with the other trees, resulting in
	 * larger usable chunks.  Second, we only look at the first chunk in
	 * the largest segment; there may be other usable chunks in the
	 * largest segment, but we ignore them.
	 */
	uint64_t rstart = rs_get_start(rs, msp->ms_unflushed_frees);
	uint64_t rsize = rs_get_end(rs, msp->ms_unflushed_frees) - rstart;
	for (int t = 0; t < TXG_DEFER_SIZE; t++) {
		uint64_t start = 0;
		uint64_t size = 0;
		boolean_t found = range_tree_find_in(msp->ms_defer[t], rstart,
		    rsize, &start, &size);
		if (found) {
			if (rstart == start)
				return (0);
			rsize = start - rstart;
		}
	}

	uint64_t start = 0;
	uint64_t size = 0;
	boolean_t found = range_tree_find_in(msp->ms_freed, rstart,
	    rsize, &start, &size);
	if (found)
		rsize = start - rstart;

	return (rsize);
}