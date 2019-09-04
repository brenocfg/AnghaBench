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
typedef  int /*<<< orphan*/  spin_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int MALLOCX_ARENA (int /*<<< orphan*/ ) ; 
 int MALLOCX_TCACHE_NONE ; 
 unsigned int NEPOCHS ; 
 unsigned int PER_THD_NALLOCS ; 
 int /*<<< orphan*/  SPIN_INITIALIZER ; 
 int /*<<< orphan*/  arena_ind ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_u_eq (unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  atomic_fetch_add_u (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int atomic_load_u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoch ; 
 void* mallocx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfinished ; 
 int /*<<< orphan*/  spin_adaptive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sz ; 

__attribute__((used)) static void *
thd_start(void *arg) {
	for (unsigned next_epoch = 1; next_epoch < NEPOCHS; next_epoch++) {
		/* Busy-wait for next epoch. */
		unsigned cur_epoch;
		spin_t spinner = SPIN_INITIALIZER;
		while ((cur_epoch = atomic_load_u(&epoch, ATOMIC_ACQUIRE)) !=
		    next_epoch) {
			spin_adaptive(&spinner);
		}
		assert_u_eq(cur_epoch, next_epoch, "Unexpected epoch");

		/*
		 * Allocate.  The main thread will reset the arena, so there's
		 * no need to deallocate.
		 */
		for (unsigned i = 0; i < PER_THD_NALLOCS; i++) {
			void *p = mallocx(sz, MALLOCX_ARENA(arena_ind) |
			    MALLOCX_TCACHE_NONE
			    );
			assert_ptr_not_null(p,
			    "Unexpected mallocx() failure\n");
		}

		/* Let the main thread know we've finished this iteration. */
		atomic_fetch_add_u(&nfinished, 1, ATOMIC_RELEASE);
	}

	return NULL;
}