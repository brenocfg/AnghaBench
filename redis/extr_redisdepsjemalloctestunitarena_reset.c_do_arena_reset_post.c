#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_zu_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* background_thread_info ; 
 int /*<<< orphan*/  free (void**) ; 
 scalar_t__ have_background_thread ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ncpus ; 
 int /*<<< orphan*/ * tsdn_fetch () ; 
 int /*<<< orphan*/  vsalloc (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
do_arena_reset_post(void **ptrs, unsigned nptrs, unsigned arena_ind) {
	tsdn_t *tsdn;
	unsigned i;

	tsdn = tsdn_fetch();

	if (have_background_thread) {
		malloc_mutex_lock(tsdn,
		    &background_thread_info[arena_ind % ncpus].mtx);
	}
	/* Verify allocations no longer exist. */
	for (i = 0; i < nptrs; i++) {
		assert_zu_eq(vsalloc(tsdn, ptrs[i]), 0,
		    "Allocation should no longer exist");
	}
	if (have_background_thread) {
		malloc_mutex_unlock(tsdn,
		    &background_thread_info[arena_ind % ncpus].mtx);
	}

	free(ptrs);
}