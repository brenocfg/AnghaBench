#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  dss_prec_t ;
struct TYPE_4__ {int /*<<< orphan*/  dss_prec; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 scalar_t__ atomic_load_u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* extent_alloc_core (int /*<<< orphan*/ *,TYPE_1__*,void*,size_t,size_t,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ have_madvise_huge ; 
 int /*<<< orphan*/  pages_set_thp_state (void*,size_t) ; 

__attribute__((used)) static void *
extent_alloc_default_impl(tsdn_t *tsdn, arena_t *arena, void *new_addr,
    size_t size, size_t alignment, bool *zero, bool *commit) {
	void *ret = extent_alloc_core(tsdn, arena, new_addr, size, alignment, zero,
	    commit, (dss_prec_t)atomic_load_u(&arena->dss_prec,
	    ATOMIC_RELAXED));
	if (have_madvise_huge && ret) {
		pages_set_thp_state(ret, size);
	}
	return ret;
}