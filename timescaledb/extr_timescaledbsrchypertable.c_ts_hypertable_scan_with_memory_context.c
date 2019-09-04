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
typedef  int /*<<< orphan*/  tuple_found_func ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_name_idx_schema ; 
 int /*<<< orphan*/  Anum_hypertable_name_idx_table ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  HYPERTABLE_NAME_INDEX ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hypertable_scan_limit_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 

int
ts_hypertable_scan_with_memory_context(const char *schema, const char *table,
									   tuple_found_func tuple_found, void *data, LOCKMODE lockmode,
									   bool tuplock, MemoryContext mctx)
{
	ScanKeyData scankey[2];
	NameData schema_name, table_name;

	namestrcpy(&schema_name, schema);
	namestrcpy(&table_name, table);

	/* Perform an index scan on schema and table. */
	ScanKeyInit(&scankey[0],
				Anum_hypertable_name_idx_schema,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				NameGetDatum(&schema_name));
	ScanKeyInit(&scankey[1],
				Anum_hypertable_name_idx_table,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				NameGetDatum(&table_name));

	return hypertable_scan_limit_internal(scankey,
										  2,
										  HYPERTABLE_NAME_INDEX,
										  tuple_found,
										  data,
										  1,
										  lockmode,
										  tuplock,
										  mctx);
}