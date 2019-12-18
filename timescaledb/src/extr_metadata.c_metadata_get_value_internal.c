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
struct TYPE_5__ {int isnull; int /*<<< orphan*/  value; int /*<<< orphan*/  typeid; } ;
struct TYPE_4__ {int nkeys; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; TYPE_2__* data; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/ * scankey; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_2__ DatumValue ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_metadata_key ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  METADATA ; 
 int /*<<< orphan*/  METADATA_PKEY_IDX ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_type_to_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_tuple_get_value ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

__attribute__((used)) static Datum
metadata_get_value_internal(Datum metadata_key, Oid key_type, Oid value_type, bool *isnull,
							LOCKMODE lockmode)
{
	ScanKeyData scankey[1];
	DatumValue dv = {
		.typeid = value_type,
		.isnull = true,
	};
	Catalog *catalog = ts_catalog_get();
	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, METADATA),
		.index = catalog_get_index(catalog, METADATA, METADATA_PKEY_IDX),
		.nkeys = 1,
		.scankey = scankey,
		.tuple_found = metadata_tuple_get_value,
		.data = &dv,
		.lockmode = lockmode,
		.scandirection = ForwardScanDirection,
	};

	ScanKeyInit(&scankey[0],
				Anum_metadata_key,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				convert_type_to_name(metadata_key, key_type));

	ts_scanner_scan(&scanctx);

	if (NULL != isnull)
		*isnull = dv.isnull;

	return dv.value;
}