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
 int /*<<< orphan*/  ALIGNMENT_CEILING (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* pages_map (void*,size_t,int /*<<< orphan*/ ,int*) ; 

void *
extent_alloc_mmap(void *new_addr, size_t size, size_t alignment, bool *zero,
    bool *commit) {
	void *ret = pages_map(new_addr, size, ALIGNMENT_CEILING(alignment,
	    PAGE), commit);
	if (ret == NULL) {
		return NULL;
	}
	assert(ret != NULL);
	if (*commit) {
		*zero = true;
	}
	return ret;
}