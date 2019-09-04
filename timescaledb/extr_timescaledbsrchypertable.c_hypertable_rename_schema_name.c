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
struct TYPE_4__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_5__ {int /*<<< orphan*/  chunk_sizing_func_schema; int /*<<< orphan*/  associated_schema_name; int /*<<< orphan*/  schema_name; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FormData_hypertable ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
hypertable_rename_schema_name(TupleInfo *ti, void *data)
{
	const char **schema_names = (const char **) data;
	const char *old_schema_name = schema_names[0];
	const char *new_schema_name = schema_names[1];
	bool updated = false;

	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_hypertable *ht = (FormData_hypertable *) GETSTRUCT(tuple);

	/*
	 * Because we are doing a heap scan with no scankey, we don't know which
	 * schema name to change, if any
	 */
	if (namestrcmp(&ht->schema_name, old_schema_name) == 0)
	{
		namestrcpy(&ht->schema_name, new_schema_name);
		updated = true;
	}
	if (namestrcmp(&ht->associated_schema_name, old_schema_name) == 0)
	{
		namestrcpy(&ht->associated_schema_name, new_schema_name);
		updated = true;
	}
	if (namestrcmp(&ht->chunk_sizing_func_schema, old_schema_name) == 0)
	{
		namestrcpy(&ht->chunk_sizing_func_schema, new_schema_name);
		updated = true;
	}

	/* Only update the catalog if we explicitly something */
	if (updated)
		ts_catalog_update(ti->scanrel, tuple);

	heap_freetuple(tuple);

	/* Keep going so we can change the name for all hypertables */
	return SCAN_CONTINUE;
}