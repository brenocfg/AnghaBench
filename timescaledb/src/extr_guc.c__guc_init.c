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
 int /*<<< orphan*/  DefineCustomBoolVariable (char*,char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefineCustomEnumVariable (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefineCustomIntVariable (char*,char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefineCustomStringVariable (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUC_SUPERUSER_ONLY ; 
 int INT64CONST (int) ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 int PG_INT16_MAX ; 
 int /*<<< orphan*/  TELEMETRY_DEFAULT ; 
 int /*<<< orphan*/ * TS_DEFAULT_LICENSE ; 
 int /*<<< orphan*/ * assign_max_cached_chunks_per_hypertable_hook ; 
 int /*<<< orphan*/  telemetry_level_options ; 
 int /*<<< orphan*/  ts_guc_constraint_aware_append ; 
 int /*<<< orphan*/  ts_guc_disable_optimizations ; 
 int /*<<< orphan*/  ts_guc_enable_chunk_append ; 
 int /*<<< orphan*/  ts_guc_enable_constraint_exclusion ; 
 int /*<<< orphan*/  ts_guc_enable_ordered_append ; 
 int /*<<< orphan*/  ts_guc_enable_parallel_chunk_append ; 
 int /*<<< orphan*/  ts_guc_enable_runtime_exclusion ; 
 int /*<<< orphan*/  ts_guc_enable_transparent_decompression ; 
 int /*<<< orphan*/  ts_guc_license_key ; 
 int /*<<< orphan*/  ts_guc_max_cached_chunks_per_hypertable ; 
 int /*<<< orphan*/  ts_guc_max_open_chunks_per_insert ; 
 int /*<<< orphan*/  ts_guc_optimize_non_hypertables ; 
 int /*<<< orphan*/  ts_guc_restoring ; 
 int /*<<< orphan*/  ts_guc_telemetry_level ; 
 int /*<<< orphan*/  ts_last_tune_time ; 
 int /*<<< orphan*/  ts_last_tune_version ; 
 int /*<<< orphan*/ * ts_license_on_assign ; 
 int /*<<< orphan*/ * ts_license_update_check ; 
 int /*<<< orphan*/  ts_shutdown_bgw ; 
 int /*<<< orphan*/  ts_telemetry_cloud ; 
 int work_mem ; 

void
_guc_init(void)
{
	/* Main database to connect to. */
	DefineCustomBoolVariable("timescaledb.disable_optimizations",
							 "Disable all timescale query optimizations",
							 NULL,
							 &ts_guc_disable_optimizations,
							 false,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);
	DefineCustomBoolVariable("timescaledb.optimize_non_hypertables",
							 "Apply timescale query optimization to plain tables",
							 "Apply timescale query optimization to plain tables in addition to "
							 "hypertables",
							 &ts_guc_optimize_non_hypertables,
							 false,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.restoring",
							 "Install timescale in restoring mode",
							 "Used for running pg_restore",
							 &ts_guc_restoring,
							 false,
							 PGC_SUSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.constraint_aware_append",
							 "Enable constraint-aware append scans",
							 "Enable constraint exclusion at execution time",
							 &ts_guc_constraint_aware_append,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_ordered_append",
							 "Enable ordered append scans",
							 "Enable ordered append optimization for queries that are ordered by "
							 "the time dimension",
							 &ts_guc_enable_ordered_append,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_chunk_append",
							 "Enable chunk append node",
							 "Enable using chunk append node",
							 &ts_guc_enable_chunk_append,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_parallel_chunk_append",
							 "Enable parallel chunk append node",
							 "Enable using parallel aware chunk append node",
							 &ts_guc_enable_parallel_chunk_append,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_runtime_exclusion",
							 "Enable runtime chunk exclusion",
							 "Enable runtime chunk exclusion in ChunkAppend node",
							 &ts_guc_enable_runtime_exclusion,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_constraint_exclusion",
							 "Enable constraint exclusion",
							 "Enable planner constraint exclusion",
							 &ts_guc_enable_constraint_exclusion,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("timescaledb.enable_transparent_decompression",
							 "Enable transparent decompression",
							 "Enable transparent decompression when querying hypertable",
							 &ts_guc_enable_transparent_decompression,
							 true,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomIntVariable("timescaledb.max_open_chunks_per_insert",
							"Maximum open chunks per insert",
							"Maximum number of open chunk tables per insert",
							&ts_guc_max_open_chunks_per_insert,
							Min(work_mem * INT64CONST(1024) / INT64CONST(25000),
								PG_INT16_MAX), /* Measurements via
												* `MemoryContextStats(TopMemoryContext)`
												* show chunk insert
												* state memory context
												* takes up ~25K bytes
												* (work_mem is in
												* kbytes) */
							0,
							PG_INT16_MAX,
							PGC_USERSET,
							0,
							NULL,
							NULL,
							NULL);

	DefineCustomIntVariable("timescaledb.max_cached_chunks_per_hypertable",
							"Maximum cached chunks",
							"Maximum number of chunks stored in the cache",
							&ts_guc_max_cached_chunks_per_hypertable,
							100,
							0,
							65536,
							PGC_USERSET,
							0,
							NULL,
							assign_max_cached_chunks_per_hypertable_hook,
							NULL);
	DefineCustomEnumVariable("timescaledb.telemetry_level",
							 "Telemetry settings level",
							 "Level used to determine which telemetry to send",
							 &ts_guc_telemetry_level,
							 TELEMETRY_DEFAULT,
							 telemetry_level_options,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomStringVariable(/* name= */ "timescaledb.license_key",
							   /* short_dec= */ "TimescaleDB license key",
							   /* long_dec= */ "Determines which features are enabled",
							   /* valueAddr= */ &ts_guc_license_key,
							   /* bootValue= */ TS_DEFAULT_LICENSE,
							   /* context= */ PGC_SUSET,
							   /* flags= */ GUC_SUPERUSER_ONLY,
							   /* check_hook= */ ts_license_update_check,
							   /* assign_hook= */ ts_license_on_assign,
							   /* show_hook= */ NULL);

	DefineCustomStringVariable(/* name= */ "timescaledb.last_tuned",
							   /* short_dec= */ "last tune run",
							   /* long_dec= */ "records last time timescaledb-tune ran",
							   /* valueAddr= */ &ts_last_tune_time,
							   /* bootValue= */ NULL,
							   /* context= */ PGC_SIGHUP,
							   /* flags= */ 0,
							   /* check_hook= */ NULL,
							   /* assign_hook= */ NULL,
							   /* show_hook= */ NULL);

	DefineCustomStringVariable(/* name= */ "timescaledb.last_tuned_version",
							   /* short_dec= */ "version of timescaledb-tune",
							   /* long_dec= */ "version of timescaledb-tune used to tune",
							   /* valueAddr= */ &ts_last_tune_version,
							   /* bootValue= */ NULL,
							   /* context= */ PGC_SIGHUP,
							   /* flags= */ 0,
							   /* check_hook= */ NULL,
							   /* assign_hook= */ NULL,
							   /* show_hook= */ NULL);

	DefineCustomStringVariable(/* name= */ "timescaledb_telemetry.cloud",
							   /* short_dec= */ "cloud provider",
							   /* long_dec= */ "cloud provider used for this instance",
							   /* valueAddr= */ &ts_telemetry_cloud,
							   /* bootValue= */ NULL,
							   /* context= */ PGC_SIGHUP,
							   /* flags= */ 0,
							   /* check_hook= */ NULL,
							   /* assign_hook= */ NULL,
							   /* show_hook= */ NULL);

#ifdef TS_DEBUG
	DefineCustomBoolVariable(/* name= */ "timescaledb.shutdown_bgw_scheduler",
							 /* short_dec= */ "immediately shutdown the bgw scheduler",
							 /* long_dec= */ "this is for debugging purposes",
							 /* valueAddr= */ &ts_shutdown_bgw,
							 /* bootValue= */ false,
							 /* context= */ PGC_SIGHUP,
							 /* flags= */ 0,
							 /* check_hook= */ NULL,
							 /* assign_hook= */ NULL,
							 /* show_hook= */ NULL);
#endif
}