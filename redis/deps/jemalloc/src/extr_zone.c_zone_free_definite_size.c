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
typedef  int /*<<< orphan*/  malloc_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 size_t ivsalloc (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  je_free (void*) ; 
 int /*<<< orphan*/  tsdn_fetch () ; 

__attribute__((used)) static void
zone_free_definite_size(malloc_zone_t *zone, void *ptr, size_t size) {
	size_t alloc_size;

	alloc_size = ivsalloc(tsdn_fetch(), ptr);
	if (alloc_size != 0) {
		assert(alloc_size == size);
		je_free(ptr);
		return;
	}

	free(ptr);
}