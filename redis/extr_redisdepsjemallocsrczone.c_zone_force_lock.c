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
 int getpid () ; 
 scalar_t__ isthreaded ; 
 int /*<<< orphan*/  jemalloc_prefork () ; 
 int zone_force_lock_pid ; 

__attribute__((used)) static void
zone_force_lock(malloc_zone_t *zone) {
	if (isthreaded) {
		/*
		 * See the note in zone_force_unlock, below, to see why we need
		 * this.
		 */
		assert(zone_force_lock_pid == -1);
		zone_force_lock_pid = getpid();
		jemalloc_prefork();
	}
}