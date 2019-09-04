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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  arena_stats_u64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
ctl_arena_stats_read_u64(arena_stats_u64_t *p) {
#ifdef JEMALLOC_ATOMIC_U64
	return atomic_load_u64(p, ATOMIC_RELAXED);
#else
	return *p;
#endif
}