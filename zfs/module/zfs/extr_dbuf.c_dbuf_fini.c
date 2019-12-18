#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int hash_table_mask; int /*<<< orphan*/  hash_table; int /*<<< orphan*/ * hash_mutexes; } ;
typedef  TYPE_1__ dbuf_hash_table_t ;
typedef  size_t dbuf_cached_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int DBUF_MUTEXES ; 
 size_t DB_CACHE_MAX ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbu_evict_taskq ; 
 TYPE_3__* dbuf_caches ; 
 int /*<<< orphan*/  dbuf_evict_cv ; 
 int /*<<< orphan*/  dbuf_evict_lock ; 
 scalar_t__ dbuf_evict_thread_exit ; 
 TYPE_1__ dbuf_hash_table ; 
 int /*<<< orphan*/  dbuf_kmem_cache ; 
 int /*<<< orphan*/ * dbuf_ksp ; 
 int /*<<< orphan*/  dbuf_stats_destroy () ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kstat_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

void
dbuf_fini(void)
{
	dbuf_hash_table_t *h = &dbuf_hash_table;
	int i;

	dbuf_stats_destroy();

	for (i = 0; i < DBUF_MUTEXES; i++)
		mutex_destroy(&h->hash_mutexes[i]);
#if defined(_KERNEL)
	/*
	 * Large allocations which do not require contiguous pages
	 * should be using vmem_free() in the linux kernel
	 */
	vmem_free(h->hash_table, (h->hash_table_mask + 1) * sizeof (void *));
#else
	kmem_free(h->hash_table, (h->hash_table_mask + 1) * sizeof (void *));
#endif
	kmem_cache_destroy(dbuf_kmem_cache);
	taskq_destroy(dbu_evict_taskq);

	mutex_enter(&dbuf_evict_lock);
	dbuf_evict_thread_exit = B_TRUE;
	while (dbuf_evict_thread_exit) {
		cv_signal(&dbuf_evict_cv);
		cv_wait(&dbuf_evict_cv, &dbuf_evict_lock);
	}
	mutex_exit(&dbuf_evict_lock);

	mutex_destroy(&dbuf_evict_lock);
	cv_destroy(&dbuf_evict_cv);

	for (dbuf_cached_state_t dcs = 0; dcs < DB_CACHE_MAX; dcs++) {
		zfs_refcount_destroy(&dbuf_caches[dcs].size);
		multilist_destroy(dbuf_caches[dcs].cache);
	}

	if (dbuf_ksp != NULL) {
		kstat_delete(dbuf_ksp);
		dbuf_ksp = NULL;
	}
}