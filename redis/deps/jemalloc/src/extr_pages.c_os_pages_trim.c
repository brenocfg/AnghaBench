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
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* os_pages_map (void*,size_t,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  os_pages_unmap (void*,size_t) ; 

__attribute__((used)) static void *
os_pages_trim(void *addr, size_t alloc_size, size_t leadsize, size_t size,
    bool *commit) {
	void *ret = (void *)((uintptr_t)addr + leadsize);

	assert(alloc_size >= leadsize + size);
#ifdef _WIN32
	os_pages_unmap(addr, alloc_size);
	void *new_addr = os_pages_map(ret, size, PAGE, commit);
	if (new_addr == ret) {
		return ret;
	}
	if (new_addr != NULL) {
		os_pages_unmap(new_addr, size);
	}
	return NULL;
#else
	size_t trailsize = alloc_size - leadsize - size;

	if (leadsize != 0) {
		os_pages_unmap(addr, leadsize);
	}
	if (trailsize != 0) {
		os_pages_unmap((void *)((uintptr_t)ret + size), trailsize);
	}
	return ret;
#endif
}