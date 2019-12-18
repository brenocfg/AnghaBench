#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_1__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_NAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_STR ; 
 int /*<<< orphan*/  ZPOOL_HIST_TXG ; 
 scalar_t__ dmu_tx_is_syncing (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_1__*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 char* kmem_vasprintf (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_sync (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ spa_is_initializing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
log_internal(nvlist_t *nvl, const char *operation, spa_t *spa,
    dmu_tx_t *tx, const char *fmt, va_list adx)
{
	char *msg;

	/*
	 * If this is part of creating a pool, not everything is
	 * initialized yet, so don't bother logging the internal events.
	 * Likewise if the pool is not writeable.
	 */
	if (spa_is_initializing(spa) || !spa_writeable(spa)) {
		fnvlist_free(nvl);
		return;
	}

	msg = kmem_vasprintf(fmt, adx);
	fnvlist_add_string(nvl, ZPOOL_HIST_INT_STR, msg);
	kmem_strfree(msg);

	fnvlist_add_string(nvl, ZPOOL_HIST_INT_NAME, operation);
	fnvlist_add_uint64(nvl, ZPOOL_HIST_TXG, tx->tx_txg);

	if (dmu_tx_is_syncing(tx)) {
		spa_history_log_sync(nvl, tx);
	} else {
		dsl_sync_task_nowait(spa_get_dsl(spa),
		    spa_history_log_sync, nvl, 0, ZFS_SPACE_CHECK_NONE, tx);
	}
	/* spa_history_log_sync() will free nvl */
}