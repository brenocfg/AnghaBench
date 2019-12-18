#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ tcaches_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* tcaches ; 
 TYPE_1__* tcaches_avail ; 
 int /*<<< orphan*/ * tcaches_elm_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tcaches_mtx ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
tcaches_destroy(tsd_t *tsd, unsigned ind) {
	malloc_mutex_lock(tsd_tsdn(tsd), &tcaches_mtx);
	tcaches_t *elm = &tcaches[ind];
	tcache_t *tcache = tcaches_elm_remove(tsd, elm);
	elm->next = tcaches_avail;
	tcaches_avail = elm;
	malloc_mutex_unlock(tsd_tsdn(tsd), &tcaches_mtx);
	if (tcache != NULL) {
		tcache_destroy(tsd, tcache, false);
	}
}