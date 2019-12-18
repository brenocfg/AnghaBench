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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  BGW_JOB_STAT ; 
 int /*<<< orphan*/  DT_NOBEGIN ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ShareRowExclusiveLock ; 
 int /*<<< orphan*/  bgw_job_stat_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_scan_job_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_tuple_mark_start ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_get () ; 

void
ts_bgw_job_stat_mark_start(int32 bgw_job_id)
{
	/* Use double-check locking */
	if (!bgw_job_stat_scan_job_id(bgw_job_id,
								  bgw_job_stat_tuple_mark_start,
								  NULL,
								  NULL,
								  RowExclusiveLock))
	{
		Relation rel =
			heap_open(catalog_get_table_id(ts_catalog_get(), BGW_JOB_STAT), ShareRowExclusiveLock);
		/* Recheck while having a self-exclusive lock */
		if (!bgw_job_stat_scan_job_id(bgw_job_id,
									  bgw_job_stat_tuple_mark_start,
									  NULL,
									  NULL,
									  RowExclusiveLock))
			bgw_job_stat_insert_relation(rel, bgw_job_id, true, DT_NOBEGIN);
		heap_close(rel, ShareRowExclusiveLock);
	}
}