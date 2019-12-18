#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_6__ {int /*<<< orphan*/  rank; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock_order; TYPE_1__ witness; } ;
typedef  TYPE_2__ malloc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ malloc_mutex_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  malloc_printf (char*) ; 
 scalar_t__ opt_abort ; 

void
malloc_mutex_postfork_child(tsdn_t *tsdn, malloc_mutex_t *mutex) {
#ifdef JEMALLOC_MUTEX_INIT_CB
	malloc_mutex_unlock(tsdn, mutex);
#else
	if (malloc_mutex_init(mutex, mutex->witness.name,
	    mutex->witness.rank, mutex->lock_order)) {
		malloc_printf("<jemalloc>: Error re-initializing mutex in "
		    "child\n");
		if (opt_abort) {
			abort();
		}
	}
#endif
}