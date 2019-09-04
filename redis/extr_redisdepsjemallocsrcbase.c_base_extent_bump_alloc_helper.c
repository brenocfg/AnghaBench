#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 uintptr_t ALIGNMENT_CEILING (uintptr_t,size_t) ; 
 size_t QUANTUM ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_binit (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ) ; 
 size_t extent_bsize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_sn_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
base_extent_bump_alloc_helper(extent_t *extent, size_t *gap_size, size_t size,
    size_t alignment) {
	void *ret;

	assert(alignment == ALIGNMENT_CEILING(alignment, QUANTUM));
	assert(size == ALIGNMENT_CEILING(size, alignment));

	*gap_size = ALIGNMENT_CEILING((uintptr_t)extent_addr_get(extent),
	    alignment) - (uintptr_t)extent_addr_get(extent);
	ret = (void *)((uintptr_t)extent_addr_get(extent) + *gap_size);
	assert(extent_bsize_get(extent) >= *gap_size + size);
	extent_binit(extent, (void *)((uintptr_t)extent_addr_get(extent) +
	    *gap_size + size), extent_bsize_get(extent) - *gap_size - size,
	    extent_sn_get(extent));
	return ret;
}