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
 int /*<<< orphan*/  fill_prefix (void*) ; 
 int je_posix_memalign (void**,size_t,scalar_t__) ; 
 int /*<<< orphan*/  malloc_oom (size_t) ; 

int
skynet_posix_memalign(void **memptr, size_t alignment, size_t size) {
	int err = je_posix_memalign(memptr, alignment, size + PREFIX_SIZE);
	if (err) malloc_oom(size);
	fill_prefix(*memptr);
	return err;
}