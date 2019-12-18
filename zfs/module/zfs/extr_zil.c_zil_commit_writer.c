#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zl_issuer_lock; int /*<<< orphan*/  zl_spa; int /*<<< orphan*/  zl_lock; } ;
typedef  TYPE_1__ zilog_t ;
struct TYPE_9__ {scalar_t__ zcw_done; int /*<<< orphan*/ * zcw_lwb; } ;
typedef  TYPE_2__ zil_commit_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZIL_STAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_commit_writer_count ; 
 int /*<<< orphan*/  zil_get_commit_list (TYPE_1__*) ; 
 int /*<<< orphan*/  zil_process_commit_list (TYPE_1__*) ; 
 int /*<<< orphan*/  zil_prune_commit_list (TYPE_1__*) ; 

__attribute__((used)) static void
zil_commit_writer(zilog_t *zilog, zil_commit_waiter_t *zcw)
{
	ASSERT(!MUTEX_HELD(&zilog->zl_lock));
	ASSERT(spa_writeable(zilog->zl_spa));

	mutex_enter(&zilog->zl_issuer_lock);

	if (zcw->zcw_lwb != NULL || zcw->zcw_done) {
		/*
		 * It's possible that, while we were waiting to acquire
		 * the "zl_issuer_lock", another thread committed this
		 * waiter to an lwb. If that occurs, we bail out early,
		 * without processing any of the zilog's queue of itxs.
		 *
		 * On certain workloads and system configurations, the
		 * "zl_issuer_lock" can become highly contended. In an
		 * attempt to reduce this contention, we immediately drop
		 * the lock if the waiter has already been processed.
		 *
		 * We've measured this optimization to reduce CPU spent
		 * contending on this lock by up to 5%, using a system
		 * with 32 CPUs, low latency storage (~50 usec writes),
		 * and 1024 threads performing sync writes.
		 */
		goto out;
	}

	ZIL_STAT_BUMP(zil_commit_writer_count);

	zil_get_commit_list(zilog);
	zil_prune_commit_list(zilog);
	zil_process_commit_list(zilog);

out:
	mutex_exit(&zilog->zl_issuer_lock);
}