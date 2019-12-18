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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  pszind_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; scalar_t__ auto_thp_switched; } ;
typedef  TYPE_1__ base_t ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/  extent; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ base_block_t ;

/* Variables and functions */
 size_t ALIGNMENT_CEILING (size_t,size_t) ; 
 size_t HUGEPAGE_CEILING (int /*<<< orphan*/ ) ; 
 uintptr_t HUGEPAGE_MASK ; 
 scalar_t__ NPSIZES ; 
 size_t QUANTUM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  base_auto_thp_switch (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  base_extent_init (size_t*,int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ base_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,size_t) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ metadata_thp_always ; 
 scalar_t__ metadata_thp_auto ; 
 scalar_t__ metadata_thp_madvise () ; 
 scalar_t__ opt_metadata_thp ; 
 int /*<<< orphan*/  pages_huge (void*,size_t) ; 
 int /*<<< orphan*/  sz_pind2sz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sz_psz2ind (size_t) ; 
 int /*<<< orphan*/  sz_psz2u (size_t) ; 

__attribute__((used)) static base_block_t *
base_block_alloc(tsdn_t *tsdn, base_t *base, extent_hooks_t *extent_hooks,
    unsigned ind, pszind_t *pind_last, size_t *extent_sn_next, size_t size,
    size_t alignment) {
	alignment = ALIGNMENT_CEILING(alignment, QUANTUM);
	size_t usize = ALIGNMENT_CEILING(size, alignment);
	size_t header_size = sizeof(base_block_t);
	size_t gap_size = ALIGNMENT_CEILING(header_size, alignment) -
	    header_size;
	/*
	 * Create increasingly larger blocks in order to limit the total number
	 * of disjoint virtual memory ranges.  Choose the next size in the page
	 * size class series (skipping size classes that are not a multiple of
	 * HUGEPAGE), or a size large enough to satisfy the requested size and
	 * alignment, whichever is larger.
	 */
	size_t min_block_size = HUGEPAGE_CEILING(sz_psz2u(header_size + gap_size
	    + usize));
	pszind_t pind_next = (*pind_last + 1 < NPSIZES) ? *pind_last + 1 :
	    *pind_last;
	size_t next_block_size = HUGEPAGE_CEILING(sz_pind2sz(pind_next));
	size_t block_size = (min_block_size > next_block_size) ? min_block_size
	    : next_block_size;
	base_block_t *block = (base_block_t *)base_map(tsdn, extent_hooks, ind,
	    block_size);
	if (block == NULL) {
		return NULL;
	}

	if (metadata_thp_madvise()) {
		void *addr = (void *)block;
		assert(((uintptr_t)addr & HUGEPAGE_MASK) == 0 &&
		    (block_size & HUGEPAGE_MASK) == 0);
		if (opt_metadata_thp == metadata_thp_always) {
			pages_huge(addr, block_size);
		} else if (opt_metadata_thp == metadata_thp_auto &&
		    base != NULL) {
			/* base != NULL indicates this is not a new base. */
			malloc_mutex_lock(tsdn, &base->mtx);
			base_auto_thp_switch(tsdn, base);
			if (base->auto_thp_switched) {
				pages_huge(addr, block_size);
			}
			malloc_mutex_unlock(tsdn, &base->mtx);
		}
	}

	*pind_last = sz_psz2ind(block_size);
	block->size = block_size;
	block->next = NULL;
	assert(block_size >= header_size);
	base_extent_init(extent_sn_next, &block->extent,
	    (void *)((uintptr_t)block + header_size), block_size - header_size);
	return block;
}