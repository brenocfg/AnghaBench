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
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  BGW_JOB_STAT ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int bgw_job_stat_insert_mark_start_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

__attribute__((used)) static bool
bgw_job_stat_insert_mark_start(int32 bgw_job_id)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;
	bool result;

	rel = heap_open(catalog_get_table_id(catalog, BGW_JOB_STAT), RowExclusiveLock);
	result = bgw_job_stat_insert_mark_start_relation(rel, bgw_job_id);
	heap_close(rel, RowExclusiveLock);

	return result;
}