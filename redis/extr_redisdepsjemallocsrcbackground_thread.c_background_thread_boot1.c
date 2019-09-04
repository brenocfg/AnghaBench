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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */

bool
background_thread_boot1(tsdn_t *tsdn) {
#ifdef JEMALLOC_BACKGROUND_THREAD
	assert(have_background_thread);
	assert(narenas_total_get() > 0);

	if (opt_max_background_threads == MAX_BACKGROUND_THREAD_LIMIT &&
	    ncpus < MAX_BACKGROUND_THREAD_LIMIT) {
		opt_max_background_threads = ncpus;
	}
	max_background_threads = opt_max_background_threads;

	background_thread_enabled_set(tsdn, opt_background_thread);
	if (malloc_mutex_init(&background_thread_lock,
	    "background_thread_global",
	    WITNESS_RANK_BACKGROUND_THREAD_GLOBAL,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}

	background_thread_info = (background_thread_info_t *)base_alloc(tsdn,
	    b0get(), opt_max_background_threads *
	    sizeof(background_thread_info_t), CACHELINE);
	if (background_thread_info == NULL) {
		return true;
	}

	for (unsigned i = 0; i < max_background_threads; i++) {
		background_thread_info_t *info = &background_thread_info[i];
		/* Thread mutex is rank_inclusive because of thread0. */
		if (malloc_mutex_init(&info->mtx, "background_thread",
		    WITNESS_RANK_BACKGROUND_THREAD,
		    malloc_mutex_address_ordered)) {
			return true;
		}
		if (pthread_cond_init(&info->cond, NULL)) {
			return true;
		}
		malloc_mutex_lock(tsdn, &info->mtx);
		info->state = background_thread_stopped;
		background_thread_info_init(tsdn, info);
		malloc_mutex_unlock(tsdn, &info->mtx);
	}
#endif

	return false;
}