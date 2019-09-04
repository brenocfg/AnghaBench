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
struct TYPE_3__ {void* data; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  HYPERTABLE ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_rename_schema_name ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

void
ts_hypertables_rename_schema_name(const char *old_name, const char *new_name)
{
	const char *schema_names[2] = { old_name, new_name };
	Catalog *catalog = ts_catalog_get();

	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, HYPERTABLE),
		.index = InvalidOid,
		.tuple_found = hypertable_rename_schema_name,
		.data = (void *) schema_names,
		.lockmode = RowExclusiveLock,
		.scandirection = ForwardScanDirection,
	};

	ts_scanner_scan(&scanctx);
}