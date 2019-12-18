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
 int MAP_ANON ; 
 int MAP_NORESERVE ; 
 int MAP_PRIVATE ; 
 scalar_t__ PAGE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_thp_state () ; 
 int /*<<< orphan*/  malloc_write (char*) ; 
 int mmap_flags ; 
 scalar_t__ opt_abort ; 
 int os_overcommits ; 
 int os_overcommits_proc () ; 
 int os_overcommits_sysctl () ; 
 scalar_t__ os_page ; 
 scalar_t__ os_page_detect () ; 
 void* os_pages_map (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  os_pages_unmap (void*,scalar_t__) ; 
 scalar_t__ pages_can_purge_lazy ; 
 int pages_can_purge_lazy_runtime ; 
 scalar_t__ pages_purge_lazy (void*,scalar_t__) ; 

bool
pages_boot(void) {
	os_page = os_page_detect();
	if (os_page > PAGE) {
		malloc_write("<jemalloc>: Unsupported system page size\n");
		if (opt_abort) {
			abort();
		}
		return true;
	}

#ifndef _WIN32
	mmap_flags = MAP_PRIVATE | MAP_ANON;
#endif

#ifdef JEMALLOC_SYSCTL_VM_OVERCOMMIT
	os_overcommits = os_overcommits_sysctl();
#elif defined(JEMALLOC_PROC_SYS_VM_OVERCOMMIT_MEMORY)
	os_overcommits = os_overcommits_proc();
#  ifdef MAP_NORESERVE
	if (os_overcommits) {
		mmap_flags |= MAP_NORESERVE;
	}
#  endif
#else
	os_overcommits = false;
#endif

	init_thp_state();

	/* Detect lazy purge runtime support. */
	if (pages_can_purge_lazy) {
		bool committed = false;
		void *madv_free_page = os_pages_map(NULL, PAGE, PAGE, &committed);
		if (madv_free_page == NULL) {
			return true;
		}
		assert(pages_can_purge_lazy_runtime);
		if (pages_purge_lazy(madv_free_page, PAGE)) {
			pages_can_purge_lazy_runtime = false;
		}
		os_pages_unmap(madv_free_page, PAGE);
	}

	return false;
}