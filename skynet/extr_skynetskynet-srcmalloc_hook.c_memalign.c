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
 scalar_t__ PREFIX_SIZE ; 
 void* fill_prefix (void*) ; 
 void* je_memalign (size_t,scalar_t__) ; 
 int /*<<< orphan*/  malloc_oom (size_t) ; 

void *
skynet_memalign(size_t alignment, size_t size) {
	void* ptr = je_memalign(alignment, size + PREFIX_SIZE);
	if(!ptr) malloc_oom(size);
	return fill_prefix(ptr);
}