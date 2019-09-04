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
 void* PAGE_ADDR2BASE (void*) ; 
 size_t PAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/  pages_can_purge_lazy ; 
 int /*<<< orphan*/  pages_can_purge_lazy_runtime ; 

bool
pages_purge_lazy(void *addr, size_t size) {
	assert(PAGE_ADDR2BASE(addr) == addr);
	assert(PAGE_CEILING(size) == size);

	if (!pages_can_purge_lazy) {
		return true;
	}
	if (!pages_can_purge_lazy_runtime) {
		/*
		 * Built with lazy purge enabled, but detected it was not
		 * supported on the current system.
		 */
		return true;
	}

#ifdef _WIN32
	VirtualAlloc(addr, size, MEM_RESET, PAGE_READWRITE);
	return false;
#elif defined(JEMALLOC_PURGE_MADVISE_FREE)
	return (madvise(addr, size,
#  ifdef MADV_FREE
	    MADV_FREE
#  else
	    JEMALLOC_MADV_FREE
#  endif
	    ) != 0);
#elif defined(JEMALLOC_PURGE_MADVISE_DONTNEED) && \
    !defined(JEMALLOC_PURGE_MADVISE_DONTNEED_ZEROS)
	return (madvise(addr, size, MADV_DONTNEED) != 0);
#else
	not_reached();
#endif
}