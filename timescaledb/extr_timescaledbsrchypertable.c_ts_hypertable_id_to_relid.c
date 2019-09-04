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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int nkeys; int /*<<< orphan*/  scandirection; int /*<<< orphan*/  lockmode; int /*<<< orphan*/ * data; int /*<<< orphan*/  tuple_found; int /*<<< orphan*/ * scankey; int /*<<< orphan*/  index; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ ScannerCtx ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_hypertable_pkey_idx_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  HYPERTABLE ; 
 int /*<<< orphan*/  HYPERTABLE_ID_INDEX ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_tuple_get_relid ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scanner_scan (TYPE_1__*) ; 

Oid
ts_hypertable_id_to_relid(int32 hypertable_id)
{
	Catalog *catalog = ts_catalog_get();
	Oid relid = InvalidOid;
	ScanKeyData scankey[1];
	ScannerCtx scanctx = {
		.table = catalog_get_table_id(catalog, HYPERTABLE),
		.index = catalog_get_index(catalog, HYPERTABLE, HYPERTABLE_ID_INDEX),
		.nkeys = 1,
		.scankey = scankey,
		.tuple_found = hypertable_tuple_get_relid,
		.data = &relid,
		.lockmode = AccessShareLock,
		.scandirection = ForwardScanDirection,
	};

	/* Perform an index scan on the hypertable pkey. */
	ScanKeyInit(&scankey[0],
				Anum_hypertable_pkey_idx_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(hypertable_id));

	ts_scanner_scan(&scanctx);

	return relid;
}