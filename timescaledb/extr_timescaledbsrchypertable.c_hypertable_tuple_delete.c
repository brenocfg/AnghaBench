#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_id ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_bgw_policy_delete_by_hypertable_id (int) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_delete_by_hypertable_id (int) ; 
 int /*<<< orphan*/  ts_continuous_agg_drop_hypertable_callback (int) ; 
 int /*<<< orphan*/  ts_dimension_delete_by_hypertable_id (int,int) ; 
 int /*<<< orphan*/  ts_tablespace_delete (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
hypertable_tuple_delete(TupleInfo *ti, void *data)
{
	CatalogSecurityContext sec_ctx;
	bool isnull;
	int hypertable_id = heap_getattr(ti->tuple, Anum_hypertable_id, ti->desc, &isnull);

	ts_tablespace_delete(hypertable_id, NULL);
	ts_chunk_delete_by_hypertable_id(hypertable_id);
	ts_dimension_delete_by_hypertable_id(hypertable_id, true);

	/* Also remove any policy argument / job that uses this hypertable */
	ts_bgw_policy_delete_by_hypertable_id(hypertable_id);

	/* Remove any dependent continuous aggs */
	ts_continuous_agg_drop_hypertable_callback(hypertable_id);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_delete(ti->scanrel, ti->tuple);
	ts_catalog_restore_user(&sec_ctx);

	return SCAN_CONTINUE;
}