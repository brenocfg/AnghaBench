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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t LARGE_MAXCLASS ; 
 size_t LARGE_MINCLASS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* extent_addr_get (int /*<<< orphan*/ *) ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdalloct (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* large_ralloc_move_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  large_ralloc_no_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void *
large_ralloc(tsdn_t *tsdn, arena_t *arena, extent_t *extent, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache) {
	size_t oldusize = extent_usize_get(extent);

	/* The following should have been caught by callers. */
	assert(usize > 0 && usize <= LARGE_MAXCLASS);
	/* Both allocation sizes must be large to avoid a move. */
	assert(oldusize >= LARGE_MINCLASS && usize >= LARGE_MINCLASS);

	/* Try to avoid moving the allocation. */
	if (!large_ralloc_no_move(tsdn, extent, usize, usize, zero)) {
		return extent_addr_get(extent);
	}

	/*
	 * usize and old size are different enough that we need to use a
	 * different size class.  In that case, fall back to allocating new
	 * space and copying.
	 */
	void *ret = large_ralloc_move_helper(tsdn, arena, usize, alignment,
	    zero);
	if (ret == NULL) {
		return NULL;
	}

	size_t copysize = (usize < oldusize) ? usize : oldusize;
	memcpy(ret, extent_addr_get(extent), copysize);
	isdalloct(tsdn, extent_addr_get(extent), oldusize, tcache, NULL, true);
	return ret;
}