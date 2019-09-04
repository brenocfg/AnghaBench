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

/* Variables and functions */
 void* ALIGNMENT_ADDR2BASE (void*,size_t) ; 
 scalar_t__ ALIGNMENT_ADDR2OFFSET (void*,size_t) ; 
 size_t PAGE ; 
 void* PAGE_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  os_page ; 
 void* os_pages_map (void*,size_t,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  os_pages_unmap (void*,size_t) ; 
 void* pages_map_slow (size_t,size_t,int*) ; 

void *
pages_map(void *addr, size_t size, size_t alignment, bool *commit) {
	assert(alignment >= PAGE);
	assert(ALIGNMENT_ADDR2BASE(addr, alignment) == addr);

	/*
	 * Ideally, there would be a way to specify alignment to mmap() (like
	 * NetBSD has), but in the absence of such a feature, we have to work
	 * hard to efficiently create aligned mappings.  The reliable, but
	 * slow method is to create a mapping that is over-sized, then trim the
	 * excess.  However, that always results in one or two calls to
	 * os_pages_unmap(), and it can leave holes in the process's virtual
	 * memory map if memory grows downward.
	 *
	 * Optimistically try mapping precisely the right amount before falling
	 * back to the slow method, with the expectation that the optimistic
	 * approach works most of the time.
	 */

	void *ret = os_pages_map(addr, size, os_page, commit);
	if (ret == NULL || ret == addr) {
		return ret;
	}
	assert(addr == NULL);
	if (ALIGNMENT_ADDR2OFFSET(ret, alignment) != 0) {
		os_pages_unmap(ret, size);
		return pages_map_slow(size, alignment, commit);
	}

	assert(PAGE_ADDR2BASE(ret) == ret);
	return ret;
}