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
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PAGE_ALLOC_COSTLY_ORDER ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 size_t PAGE_SIZE ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __GFP_RECLAIM ; 
 int __GFP_RETRY_MAYFAIL ; 
 void* __vmalloc (size_t,int,int /*<<< orphan*/ ) ; 
 void* kmalloc_node (size_t,int,int /*<<< orphan*/ ) ; 
 void* kvmalloc (size_t,int) ; 

void *
spl_kvmalloc(size_t size, gfp_t lflags)
{
#ifdef HAVE_KVMALLOC
	/*
	 * GFP_KERNEL allocations can safely use kvmalloc which may
	 * improve performance by avoiding a) high latency caused by
	 * vmalloc's on-access allocation, b) performance loss due to
	 * MMU memory address mapping and c) vmalloc locking overhead.
	 * This has the side-effect that the slab statistics will
	 * incorrectly report this as a vmem allocation, but that is
	 * purely cosmetic.
	 */
	if ((lflags & GFP_KERNEL) == GFP_KERNEL)
		return (kvmalloc(size, lflags));
#endif

	gfp_t kmalloc_lflags = lflags;

	if (size > PAGE_SIZE) {
		/*
		 * We need to set __GFP_NOWARN here since spl_kvmalloc is not
		 * only called by spl_kmem_alloc_impl but can be called
		 * directly with custom lflags, too. In that case
		 * kmem_flags_convert does not get called, which would
		 * implicitly set __GFP_NOWARN.
		 */
		kmalloc_lflags |= __GFP_NOWARN;

		/*
		 * N.B. __GFP_RETRY_MAYFAIL is supported only for large
		 * e (>32kB) allocations.
		 *
		 * We have to override __GFP_RETRY_MAYFAIL by __GFP_NORETRY
		 * for !costly requests because there is no other way to tell
		 * the allocator that we want to fail rather than retry
		 * endlessly.
		 */
		if (!(kmalloc_lflags & __GFP_RETRY_MAYFAIL) ||
		    (size <= PAGE_SIZE << PAGE_ALLOC_COSTLY_ORDER)) {
			kmalloc_lflags |= __GFP_NORETRY;
		}
	}

	/*
	 * We first try kmalloc - even for big sizes - and fall back to
	 * __vmalloc if that fails.
	 *
	 * For non-__GFP-RECLAIM allocations we always stick to
	 * kmalloc_node, and fail when kmalloc is not successful (returns
	 * NULL).
	 * We cannot fall back to __vmalloc in this case because __vmalloc
	 * internally uses GPF_KERNEL allocations.
	 */
	void *ptr = kmalloc_node(size, kmalloc_lflags, NUMA_NO_NODE);
	if (ptr || size <= PAGE_SIZE ||
	    (lflags & __GFP_RECLAIM) != __GFP_RECLAIM) {
		return (ptr);
	}

	return (__vmalloc(size, lflags | __GFP_HIGHMEM, PAGE_KERNEL));
}