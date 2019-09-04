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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tcaches ; 
 int /*<<< orphan*/ * tcaches_elm_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcaches_mtx ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
tcaches_flush(tsd_t *tsd, unsigned ind) {
	malloc_mutex_lock(tsd_tsdn(tsd), &tcaches_mtx);
	tcache_t *tcache = tcaches_elm_remove(tsd, &tcaches[ind]);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tcaches_mtx);
	if (tcache != NULL) {
		tcache_destroy(tsd, tcache, false);
	}
}