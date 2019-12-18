#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int skc_flags; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;
struct TYPE_7__ {TYPE_1__* reclaim_state; } ;
struct TYPE_5__ {int reclaimed_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP2 (int) ; 
 int /*<<< orphan*/  IS_P2ALIGNED (void*,int /*<<< orphan*/ ) ; 
 int KMC_KMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  spl_kmem_free_impl (void*,int) ; 

__attribute__((used)) static void
kv_free(spl_kmem_cache_t *skc, void *ptr, int size)
{
	ASSERT(IS_P2ALIGNED(ptr, PAGE_SIZE));

	/*
	 * The Linux direct reclaim path uses this out of band value to
	 * determine if forward progress is being made.  Normally this is
	 * incremented by kmem_freepages() which is part of the various
	 * Linux slab implementations.  However, since we are using none
	 * of that infrastructure we are responsible for incrementing it.
	 */
	if (current->reclaim_state)
		current->reclaim_state->reclaimed_slab += size >> PAGE_SHIFT;

	if (skc->skc_flags & KMC_KMEM) {
		ASSERT(ISP2(size));
		free_pages((unsigned long)ptr, get_order(size));
	} else {
		spl_kmem_free_impl(ptr, size);
	}
}