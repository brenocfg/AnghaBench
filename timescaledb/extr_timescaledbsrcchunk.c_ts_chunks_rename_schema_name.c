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
struct TYPE_3__ {int nkeys; char* data; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/ * scankey; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_schema_name_idx_schema_name ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK ; 
 int /*<<< orphan*/  CHUNK_SCHEMA_NAME_INDEX ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_rename_schema_name ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

void
ts_chunks_rename_schema_name(char *old_schema, char *new_schema)
{
	NameData old_schema_name;
	ScanKeyData scankey[1];
	Catalog *catalog = ts_catalog_get();
	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, CHUNK),
		.index = catalog_get_index(catalog, CHUNK, CHUNK_SCHEMA_NAME_INDEX),
		.nkeys = 1,
		.scankey = scankey,
		.tuple_found = chunk_rename_schema_name,
		.data = new_schema,
		.lockmode = RowExclusiveLock,
		.scandirection = ForwardScanDirection,
	};

	namestrcpy(&old_schema_name, old_schema);

	ScanKeyInit(&scankey[0],
				Anum_chunk_schema_name_idx_schema_name,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				NameGetDatum(&old_schema_name));

	ts_scanner_scan(&scanctx);
}