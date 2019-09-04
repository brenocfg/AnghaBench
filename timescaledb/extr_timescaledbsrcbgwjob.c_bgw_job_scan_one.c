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
typedef  int /*<<< orphan*/  tuple_found_func ;
typedef  int /*<<< orphan*/  tuple_filter_func ;
struct TYPE_3__ {int nkeys; void* data; int /*<<< orphan*/  result_mctx; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  filter; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/ * scankey; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  BGW_JOB ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan_one (TYPE_1__*,int,char*) ; 

__attribute__((used)) static void
bgw_job_scan_one(int indexid, ScanKeyData scankey[], int nkeys, tuple_found_func tuple_found,
				 tuple_filter_func tuple_filter, void *data, MemoryContext mctx, LOCKMODE lockmode,
				 bool fail_if_not_found)
{
	Catalog *catalog = ts_catalog_get();
	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, BGW_JOB),
		.index = catalog_get_index(catalog, BGW_JOB, indexid),
		.nkeys = nkeys,
		.scankey = scankey,
		.tuple_found = tuple_found,
		.filter = tuple_filter,
		.data = data,
		.lockmode = lockmode,
		.scandirection = ForwardScanDirection,
		.result_mctx = mctx,
	};

	ts_scanner_scan_one(&scanctx, fail_if_not_found, "bgw job");
}