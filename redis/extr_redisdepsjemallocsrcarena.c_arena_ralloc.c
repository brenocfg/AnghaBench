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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t LARGE_MAXCLASS ; 
 size_t LARGE_MINCLASS ; 
 size_t SMALL_MAXCLASS ; 
 void* arena_ralloc_move_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_ralloc_no_move (int /*<<< orphan*/ *,void*,size_t,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iealloc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  isdalloct (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* large_ralloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 size_t sz_s2u (size_t) ; 
 scalar_t__ unlikely (int) ; 

void *
arena_ralloc(tsdn_t *tsdn, arena_t *arena, void *ptr, size_t oldsize,
    size_t size, size_t alignment, bool zero, tcache_t *tcache) {
	size_t usize = sz_s2u(size);
	if (unlikely(usize == 0 || size > LARGE_MAXCLASS)) {
		return NULL;
	}

	if (likely(usize <= SMALL_MAXCLASS)) {
		/* Try to avoid moving the allocation. */
		if (!arena_ralloc_no_move(tsdn, ptr, oldsize, usize, 0, zero)) {
			return ptr;
		}
	}

	if (oldsize >= LARGE_MINCLASS && usize >= LARGE_MINCLASS) {
		return large_ralloc(tsdn, arena, iealloc(tsdn, ptr), usize,
		    alignment, zero, tcache);
	}

	/*
	 * size and oldsize are different enough that we need to move the
	 * object.  In that case, fall back to allocating new space and copying.
	 */
	void *ret = arena_ralloc_move_helper(tsdn, arena, usize, alignment,
	    zero, tcache);
	if (ret == NULL) {
		return NULL;
	}

	/*
	 * Junk/zero-filling were already done by
	 * ipalloc()/arena_malloc().
	 */

	size_t copysize = (usize < oldsize) ? usize : oldsize;
	memcpy(ret, ptr, copysize);
	isdalloct(tsdn, ptr, oldsize, tcache, NULL, true);
	return ret;
}