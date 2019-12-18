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
 int /*<<< orphan*/  MADV_DONTDUMP ; 
 void* PAGE_ADDR2BASE (void*) ; 
 size_t PAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ madvise (void*,size_t,int /*<<< orphan*/ ) ; 

bool
pages_dontdump(void *addr, size_t size) {
	assert(PAGE_ADDR2BASE(addr) == addr);
	assert(PAGE_CEILING(size) == size);
#ifdef JEMALLOC_MADVISE_DONTDUMP
	return madvise(addr, size, MADV_DONTDUMP) != 0;
#else
	return false;
#endif
}