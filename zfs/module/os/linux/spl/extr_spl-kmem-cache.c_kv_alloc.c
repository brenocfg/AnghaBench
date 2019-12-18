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
struct TYPE_3__ {int skc_flags; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  ISP2 (int) ; 
 int /*<<< orphan*/  IS_P2ALIGNED (void*,int /*<<< orphan*/ ) ; 
 int KMC_KMEM ; 
 int KMC_KVMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_HIGHMEM ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 void* __vmalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int kmem_flags_convert (int) ; 
 void* spl_kvmalloc (int,int) ; 

__attribute__((used)) static void *
kv_alloc(spl_kmem_cache_t *skc, int size, int flags)
{
	gfp_t lflags = kmem_flags_convert(flags);
	void *ptr;

	if (skc->skc_flags & KMC_KMEM) {
		ASSERT(ISP2(size));
		ptr = (void *)__get_free_pages(lflags, get_order(size));
	} else if (skc->skc_flags & KMC_KVMEM) {
		ptr = spl_kvmalloc(size, lflags);
	} else {
		/*
		 * GFP_KERNEL allocations can safely use kvmalloc which may
		 * improve performance by avoiding a) high latency caused by
		 * vmalloc's on-access allocation, b) performance loss due to
		 * MMU memory address mapping and c) vmalloc locking overhead.
		 * This has the side-effect that the slab statistics will
		 * incorrectly report this as a vmem allocation, but that is
		 * purely cosmetic.
		 *
		 * For non-GFP_KERNEL allocations we stick to __vmalloc.
		 */
		if ((lflags & GFP_KERNEL) == GFP_KERNEL) {
			ptr = spl_kvmalloc(size, lflags);
		} else {
			ptr = __vmalloc(size, lflags | __GFP_HIGHMEM,
			    PAGE_KERNEL);
		}
	}

	/* Resulting allocated memory will be page aligned */
	ASSERT(IS_P2ALIGNED(ptr, PAGE_SIZE));

	return (ptr);
}