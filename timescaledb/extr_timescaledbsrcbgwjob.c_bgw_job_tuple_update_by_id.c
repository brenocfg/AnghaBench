#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ TupleInfo ;
struct TYPE_6__ {int /*<<< orphan*/  retry_period; int /*<<< orphan*/  max_retries; int /*<<< orphan*/  max_runtime; int /*<<< orphan*/  schedule_interval; } ;
struct TYPE_9__ {TYPE_1__ fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  retry_period; int /*<<< orphan*/  max_retries; int /*<<< orphan*/  max_runtime; int /*<<< orphan*/  schedule_interval; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ FormData_bgw_job ;
typedef  TYPE_4__ BgwJob ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
bgw_job_tuple_update_by_id(TupleInfo *ti, void *const data)
{
	BgwJob *updated_job = (BgwJob *) data;
	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_bgw_job *fd = (FormData_bgw_job *) GETSTRUCT(tuple);

	fd->schedule_interval = updated_job->fd.schedule_interval;
	fd->max_runtime = updated_job->fd.max_runtime;
	fd->max_retries = updated_job->fd.max_retries;
	fd->retry_period = updated_job->fd.retry_period;

	ts_catalog_update(ti->scanrel, tuple);
	heap_freetuple(tuple);
	return SCAN_DONE;
}