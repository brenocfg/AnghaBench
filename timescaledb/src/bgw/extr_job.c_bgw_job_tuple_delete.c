#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_2__ FormData_bgw_job ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  ts_bgw_job_stat_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_policy_chunk_stats_delete_row_only_by_job_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_policy_drop_chunks_delete_row_only_by_job_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_policy_reorder_delete_row_only_by_job_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
bgw_job_tuple_delete(TupleInfo *ti, void *data)
{
	CatalogSecurityContext sec_ctx;
	int32 job_id = ((FormData_bgw_job *) GETSTRUCT(ti->tuple))->id;

	/* Also delete the bgw_stat entry */
	ts_bgw_job_stat_delete(job_id);

	/* Delete any policy args associated with this job */
	ts_bgw_policy_reorder_delete_row_only_by_job_id(job_id);
	ts_bgw_policy_drop_chunks_delete_row_only_by_job_id(job_id);

	/* Delete any stats in bgw_policy_chunk_stats related to this job */
	ts_bgw_policy_chunk_stats_delete_row_only_by_job_id(job_id);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_delete(ti->scanrel, ti->tuple);
	ts_catalog_restore_user(&sec_ctx);

	return SCAN_CONTINUE;
}