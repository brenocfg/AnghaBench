#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_6__* tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_8__ {int /*<<< orphan*/  chunk_sizing_func_schema; int /*<<< orphan*/  associated_schema_name; int /*<<< orphan*/  schema_name; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FormData_hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_formdata_fill (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_formdata_make_tuple (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ts_catalog_update_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
hypertable_rename_schema_name(TupleInfo *ti, void *data)
{
	const char **schema_names = (const char **) data;
	const char *old_schema_name = schema_names[0];
	const char *new_schema_name = schema_names[1];
	bool updated = false;
	FormData_hypertable fd;

	hypertable_formdata_fill(&fd, ti->tuple, ti->desc);

	/*
	 * Because we are doing a heap scan with no scankey, we don't know which
	 * schema name to change, if any
	 */
	if (namestrcmp(&fd.schema_name, old_schema_name) == 0)
	{
		namestrcpy(&fd.schema_name, new_schema_name);
		updated = true;
	}
	if (namestrcmp(&fd.associated_schema_name, old_schema_name) == 0)
	{
		namestrcpy(&fd.associated_schema_name, new_schema_name);
		updated = true;
	}
	if (namestrcmp(&fd.chunk_sizing_func_schema, old_schema_name) == 0)
	{
		namestrcpy(&fd.chunk_sizing_func_schema, new_schema_name);
		updated = true;
	}

	/* Only update the catalog if we explicitly something */
	if (updated)
	{
		HeapTuple new_tuple = hypertable_formdata_make_tuple(&fd, ti->desc);
		ts_catalog_update_tid(ti->scanrel, &ti->tuple->t_self, new_tuple);
		heap_freetuple(new_tuple);
	}

	/* Keep going so we can change the name for all hypertables */
	return SCAN_CONTINUE;
}