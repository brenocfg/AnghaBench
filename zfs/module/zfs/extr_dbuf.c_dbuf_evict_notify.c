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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t DB_DBUF_CACHE ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ dbuf_cache_above_hiwater () ; 
 scalar_t__ dbuf_cache_target_bytes () ; 
 TYPE_1__* dbuf_caches ; 
 int /*<<< orphan*/  dbuf_evict_cv ; 
 int /*<<< orphan*/  dbuf_evict_one () ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_evict_notify(void)
{
	/*
	 * We check if we should evict without holding the dbuf_evict_lock,
	 * because it's OK to occasionally make the wrong decision here,
	 * and grabbing the lock results in massive lock contention.
	 */
	if (zfs_refcount_count(&dbuf_caches[DB_DBUF_CACHE].size) >
	    dbuf_cache_target_bytes()) {
		if (dbuf_cache_above_hiwater())
			dbuf_evict_one();
		cv_signal(&dbuf_evict_cv);
	}
}