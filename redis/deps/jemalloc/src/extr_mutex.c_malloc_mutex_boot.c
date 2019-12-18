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
struct TYPE_2__ {struct TYPE_2__* postponed_next; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ _pthread_mutex_init_calloc_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootstrap_calloc ; 
 int postpone_init ; 
 TYPE_1__* postponed_mutexes ; 

bool
malloc_mutex_boot(void) {
#ifdef JEMALLOC_MUTEX_INIT_CB
	postpone_init = false;
	while (postponed_mutexes != NULL) {
		if (_pthread_mutex_init_calloc_cb(&postponed_mutexes->lock,
		    bootstrap_calloc) != 0) {
			return true;
		}
		postponed_mutexes = postponed_mutexes->postponed_next;
	}
#endif
	return false;
}