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
 int /*<<< orphan*/  TIMESCALEDB_VERSION_MOD ; 
 int /*<<< orphan*/  _cache_init () ; 
 int /*<<< orphan*/  _cache_invalidate_init () ; 
 int /*<<< orphan*/  _chunk_append_init () ; 
 int /*<<< orphan*/  _conn_mock_init () ; 
 int /*<<< orphan*/  _conn_plain_init () ; 
 int /*<<< orphan*/  _conn_ssl_init () ; 
 int /*<<< orphan*/  _constraint_aware_append_init () ; 
 int /*<<< orphan*/  _event_trigger_init () ; 
 int /*<<< orphan*/  _guc_init () ; 
 int /*<<< orphan*/  _hypertable_cache_init () ; 
 int /*<<< orphan*/  _planner_init () ; 
 int /*<<< orphan*/  _process_utility_init () ; 
 int /*<<< orphan*/  ts_bgw_check_loader_api_version () ; 
 int /*<<< orphan*/  ts_extension_check_server_version () ; 
 int /*<<< orphan*/  ts_extension_check_version (int /*<<< orphan*/ ) ; 

void
_PG_init(void)
{
	/*
	 * Check extension_is loaded to catch certain errors such as calls to
	 * functions defined on the wrong extension version
	 */
	ts_extension_check_version(TIMESCALEDB_VERSION_MOD);
	ts_extension_check_server_version();
	ts_bgw_check_loader_api_version();

	_cache_init();
	_hypertable_cache_init();
	_cache_invalidate_init();
	_planner_init();
	_constraint_aware_append_init();
	_chunk_append_init();
	_event_trigger_init();
	_process_utility_init();
	_guc_init();
	_conn_plain_init();
#ifdef TS_USE_OPENSSL
	_conn_ssl_init();
#endif
#ifdef TS_DEBUG
	_conn_mock_init();
#endif
}