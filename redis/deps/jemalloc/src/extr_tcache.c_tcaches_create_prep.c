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
 int /*<<< orphan*/  CACHELINE ; 
 int MALLOCX_TCACHE_MAX ; 
 int /*<<< orphan*/  b0get () ; 
 int /*<<< orphan*/ * base_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcaches ; 
 int /*<<< orphan*/ * tcaches_avail ; 
 int /*<<< orphan*/  tcaches_mtx ; 
 int tcaches_past ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tcaches_create_prep(tsd_t *tsd) {
	bool err;

	malloc_mutex_lock(tsd_tsdn(tsd), &tcaches_mtx);

	if (tcaches == NULL) {
		tcaches = base_alloc(tsd_tsdn(tsd), b0get(), sizeof(tcache_t *)
		    * (MALLOCX_TCACHE_MAX+1), CACHELINE);
		if (tcaches == NULL) {
			err = true;
			goto label_return;
		}
	}

	if (tcaches_avail == NULL && tcaches_past > MALLOCX_TCACHE_MAX) {
		err = true;
		goto label_return;
	}

	err = false;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &tcaches_mtx);
	return err;
}