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

/* Variables and functions */
 int /*<<< orphan*/  _cache_fini () ; 
 int /*<<< orphan*/  _cache_invalidate_fini () ; 
 int /*<<< orphan*/  _conn_mock_fini () ; 
 int /*<<< orphan*/  _conn_plain_fini () ; 
 int /*<<< orphan*/  _conn_ssl_fini () ; 
 int /*<<< orphan*/  _event_trigger_fini () ; 
 int /*<<< orphan*/  _guc_fini () ; 
 int /*<<< orphan*/  _hypertable_cache_fini () ; 
 int /*<<< orphan*/  _planner_fini () ; 
 int /*<<< orphan*/  _process_utility_fini () ; 

void
_PG_fini(void)
{
	/*
	 * Order of items should be strict reverse order of _PG_init. Please
	 * document any exceptions.
	 */
#ifdef TS_DEBUG
	_conn_mock_fini();
#endif
#ifdef TS_USE_OPENSSL
	_conn_ssl_fini();
#endif
	_conn_plain_fini();
	_guc_fini();
	_process_utility_fini();
	_event_trigger_fini();
	_planner_fini();
	_cache_invalidate_fini();
	_hypertable_cache_fini();
	_cache_fini();
}