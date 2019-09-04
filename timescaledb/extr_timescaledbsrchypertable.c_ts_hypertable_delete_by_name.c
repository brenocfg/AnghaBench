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
typedef  int /*<<< orphan*/  ScanKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_name_idx_schema ; 
 int /*<<< orphan*/  Anum_hypertable_name_idx_table ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  HYPERTABLE_NAME_INDEX ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hypertable_scan_limit_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_tuple_delete ; 
 int /*<<< orphan*/  namein ; 

int
ts_hypertable_delete_by_name(const char *schema_name, const char *table_name)
{
	ScanKeyData scankey[2];

	ScanKeyInit(&scankey[0],
				Anum_hypertable_name_idx_schema,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				DirectFunctionCall1(namein, CStringGetDatum(schema_name)));

	ScanKeyInit(&scankey[1],
				Anum_hypertable_name_idx_table,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				DirectFunctionCall1(namein, CStringGetDatum(table_name)));

	return hypertable_scan_limit_internal(scankey,
										  2,
										  HYPERTABLE_NAME_INDEX,
										  hypertable_tuple_delete,
										  NULL,
										  0,
										  RowExclusiveLock,
										  false,
										  CurrentMemoryContext);
}