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
struct TYPE_3__ {int nkeys; char** data; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/ * scankey; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_dimension_integer_now_func_schema ; 
 int /*<<< orphan*/  Anum_dimension_partitioning_func_schema ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DIMENSION ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_rename_schema_name ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

void
ts_dimensions_rename_schema_name(char *old_name, char *new_name)
{
	NameData old_schema_name;
	ScanKeyData scankey[1];
	Catalog *catalog = ts_catalog_get();
	char *names[2] = { old_name, new_name };

	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, DIMENSION),
		.index = InvalidOid,
		.nkeys = 1,
		.scankey = scankey,
		.tuple_found = dimension_rename_schema_name,
		.data = names,
		.lockmode = RowExclusiveLock,
		.scandirection = ForwardScanDirection,
	};

	namestrcpy(&old_schema_name, old_name);

	ScanKeyInit(&scankey[0],
				Anum_dimension_partitioning_func_schema,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				NameGetDatum(&old_schema_name));

	ts_scanner_scan(&scanctx);

	ScanKeyInit(&scankey[0],
				Anum_dimension_integer_now_func_schema,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				NameGetDatum(&old_schema_name));

	ts_scanner_scan(&scanctx);
}