#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_15__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_18__ {TYPE_2__ fd; int /*<<< orphan*/  space; } ;
struct TYPE_17__ {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * schema; } ;
struct TYPE_14__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_13__ {TYPE_1__ fd; } ;
typedef  TYPE_3__ SchemaAndName ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ InternalTimeRange ;
typedef  TYPE_5__ Hypertable ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_INT64_MAX ; 
 scalar_t__ PG_INT64_MIN ; 
 scalar_t__ completed_threshold_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  continuous_aggs_completed_threshold_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_10__* hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (TYPE_10__*) ; 
 TYPE_5__* ts_hypertable_cache_get_entry_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 scalar_t__ ts_time_bucket_by_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_materializations (TYPE_3__,TYPE_3__,int /*<<< orphan*/ *,TYPE_4__,scalar_t__,int /*<<< orphan*/ *) ; 

void
continuous_agg_execute_materialization(int64 bucket_width, int32 hypertable_id,
									   int32 materialization_id, SchemaAndName partial_view,
									   List *invalidations,
									   int64 materialization_invalidation_threshold)
{
	CatalogSecurityContext sec_ctx;
	SchemaAndName materialization_table_name;
	InternalTimeRange new_materialization_range = {
		.start = completed_threshold_get(materialization_id),
		.end = materialization_invalidation_threshold,
	};
	Cache *hcache = ts_hypertable_cache_pin();
	Hypertable *raw_table = ts_hypertable_cache_get_entry_by_id(hcache, hypertable_id);
	Hypertable *materialization_table =
		ts_hypertable_cache_get_entry_by_id(hcache, materialization_id);
	NameData time_column_name;

	Assert(new_materialization_range.start <= new_materialization_range.end);

	if (raw_table == NULL)
		elog(ERROR, "can only materialize continuous aggregates on a hypertable");

	if (materialization_table == NULL)
		elog(ERROR, "can only materialize continuous aggregates to a hypertable");

	/* The materialization table always stores our internal representation of time values, so get
	 * the real type of the time column from the original hypertable */
	new_materialization_range.type =
		ts_dimension_get_partition_type(hyperspace_get_open_dimension(raw_table->space, 0));

	time_column_name =
		hyperspace_get_open_dimension(materialization_table->space, 0)->fd.column_name;

	if (new_materialization_range.start > PG_INT64_MIN)
		Assert(new_materialization_range.start ==
			   ts_time_bucket_by_type(bucket_width,
									  new_materialization_range.start,
									  new_materialization_range.type));

	/* Since we store the invalidation threshold as an exclusive range (we invalidate any rows <
	 * invalidation_threshold) invalidations for rows containing INT64_MAX, the maximum values for
	 * that threshold, will never be processed. Since we expect it to be rare that such a row is
	 * needed, we avoid this by pinning the materialization end, and thus the invalidation threshold
	 * to be at most one time_bucket before INT64_MAX. Since we never materialize that last bucket,
	 * it never needs to be invalidated, and the invalidations can't be lost. */
	if (new_materialization_range.end < PG_INT64_MAX)
		Assert(new_materialization_range.end ==
			   ts_time_bucket_by_type(bucket_width,
									  new_materialization_range.end,
									  new_materialization_range.type));
	else
		new_materialization_range.end = ts_time_bucket_by_type(bucket_width,
															   new_materialization_range.end,
															   new_materialization_range.type);

	materialization_table_name.schema = &materialization_table->fd.schema_name;
	materialization_table_name.name = &materialization_table->fd.table_name;

	/* lock the table's we will be inserting to now, to prevent deadlocks later on */
	// TODO lock the materialization table, the and the completed_threshold with RowExclusive locks
	// TODO decide lock ordering

	update_materializations(partial_view,
							materialization_table_name,
							&time_column_name,
							new_materialization_range,
							bucket_width,
							invalidations);

	/* update the completed watermark */
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);

	continuous_aggs_completed_threshold_set(materialization_id, new_materialization_range.end);

	ts_catalog_restore_user(&sec_ctx);
	ts_cache_release(hcache);
	return;
}