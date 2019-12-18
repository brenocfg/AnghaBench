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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_FREE_JUNK ; 
 int /*<<< orphan*/  assert_u_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  large_dalloc_junk_orig (void*,size_t) ; 
 int saw_junking ; 
 void* watch_for_junking ; 

__attribute__((used)) static void
large_dalloc_junk_intercept(void *ptr, size_t usize) {
	size_t i;

	large_dalloc_junk_orig(ptr, usize);
	for (i = 0; i < usize; i++) {
		assert_u_eq(((uint8_t *)ptr)[i], JEMALLOC_FREE_JUNK,
		    "Missing junk fill for byte %zu/%zu of deallocated region",
		    i, usize);
	}
	if (ptr == watch_for_junking) {
		saw_junking = true;
	}
}