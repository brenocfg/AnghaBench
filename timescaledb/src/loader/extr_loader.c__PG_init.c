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
 int /*<<< orphan*/  CacheRegisterRelcacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefineCustomBoolVariable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUC_DISABLE_LOAD_NAME ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  extension_load_without_preload () ; 
 int /*<<< orphan*/  extension_mark_loader_present () ; 
 int /*<<< orphan*/  guc_disable_load ; 
 int /*<<< orphan*/  inval_cache_callback ; 
 int /*<<< orphan*/  post_analyze_hook ; 
 int /*<<< orphan*/  post_parse_analyze_hook ; 
 int /*<<< orphan*/  prev_post_parse_analyze_hook ; 
 int /*<<< orphan*/  prev_shmem_startup_hook ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 int /*<<< orphan*/  shmem_startup_hook ; 
 int /*<<< orphan*/  timescale_shmem_startup_hook ; 
 int /*<<< orphan*/  ts_bgw_cluster_launcher_register () ; 
 int /*<<< orphan*/  ts_bgw_counter_setup_gucs () ; 
 int /*<<< orphan*/  ts_bgw_counter_shmem_alloc () ; 
 int /*<<< orphan*/  ts_bgw_interface_register_api_version () ; 
 int /*<<< orphan*/  ts_bgw_message_queue_alloc () ; 
 int /*<<< orphan*/  ts_lwlocks_shmem_alloc () ; 

void
_PG_init(void)
{
	if (!process_shared_preload_libraries_in_progress)
	{
		extension_load_without_preload();
	}
	extension_mark_loader_present();

	elog(INFO, "timescaledb loaded");

	ts_bgw_counter_shmem_alloc();
	ts_bgw_message_queue_alloc();
	ts_lwlocks_shmem_alloc();
	ts_bgw_cluster_launcher_register();
	ts_bgw_counter_setup_gucs();
	ts_bgw_interface_register_api_version();

	/* This is a safety-valve variable to prevent loading the full extension */
	DefineCustomBoolVariable(GUC_DISABLE_LOAD_NAME,
							 "Disable the loading of the actual extension",
							 NULL,
							 &guc_disable_load,
							 false,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	/*
	 * cannot check for extension here since not inside a transaction yet. Nor
	 * do we even have an assigned database yet
	 */
	CacheRegisterRelcacheCallback(inval_cache_callback, PointerGetDatum(NULL));

	/*
	 * using the post_parse_analyze_hook since it's the earliest available
	 * hook
	 */
	prev_post_parse_analyze_hook = post_parse_analyze_hook;
	/* register shmem startup hook for the background worker stuff */
	prev_shmem_startup_hook = shmem_startup_hook;

	post_parse_analyze_hook = post_analyze_hook;
	shmem_startup_hook = timescale_shmem_startup_hook;
}