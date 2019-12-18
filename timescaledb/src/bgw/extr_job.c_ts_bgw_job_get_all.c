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
struct TYPE_5__ {size_t alloc_size; int /*<<< orphan*/ * list; } ;
struct TYPE_4__ {int /*<<< orphan*/  result_mctx; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  tuple_found; TYPE_2__* data; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Catalog ;
typedef  TYPE_2__ AccumData ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BGW_JOB ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  bgw_job_accum_tuple_found ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

extern List *
ts_bgw_job_get_all(size_t alloc_size, MemoryContext mctx)
{
	Catalog *catalog = ts_catalog_get();
	AccumData list_data = {
		.list = NIL,
		.alloc_size = alloc_size,
	};
	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, BGW_JOB),
		.index = InvalidOid,
		.data = &list_data,
		.tuple_found = bgw_job_accum_tuple_found,
		.lockmode = AccessShareLock,
		.scandirection = ForwardScanDirection,
		.result_mctx = mctx,
	};

	ts_scanner_scan(&scanctx);
	return list_data.list;
}