#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  target_size_bytes; int /*<<< orphan*/  func_name; int /*<<< orphan*/  func_schema; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  TYPE_1__ ChunkSizingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_EXISTS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_tablespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tablespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  insert_blocker_trigger_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_sizing_func_validate (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ts_chunk_sizing_info_get_default_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_is_hypertable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_tablespace_attach_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool
ts_hypertable_create_compressed(Oid table_relid, int32 hypertable_id)
{
	Oid user_oid = GetUserId();
	Oid tspc_oid = get_rel_tablespace(table_relid);
	NameData schema_name, table_name, associated_schema_name;
	ChunkSizingInfo *chunk_sizing_info;
	Relation rel;

	rel = heap_open(table_relid, AccessExclusiveLock);
	/*
	 * Check that the user has permissions to make this table to a compressed
	 * hypertable
	 */
	ts_hypertable_permissions_check(table_relid, user_oid);
	if (ts_is_hypertable(table_relid))
	{
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_EXISTS),
				 errmsg("table \"%s\" is already a hypertable", get_rel_name(table_relid))));
		heap_close(rel, AccessExclusiveLock);
	}

	namestrcpy(&schema_name, get_namespace_name(get_rel_namespace(table_relid)));
	namestrcpy(&table_name, get_rel_name(table_relid));

	/* we don't use the chunking size info for managing the compressed table.
	 * But need this to satisfy hypertable constraints
	 */
	chunk_sizing_info = ts_chunk_sizing_info_get_default_disabled(table_relid);
	ts_chunk_sizing_func_validate(chunk_sizing_info->func, chunk_sizing_info);

	/* Checks pass, now we can create the catalog information */
	namestrcpy(&schema_name, get_namespace_name(get_rel_namespace(table_relid)));
	namestrcpy(&table_name, get_rel_name(table_relid));
	namestrcpy(&associated_schema_name, INTERNAL_SCHEMA_NAME);

	/* compressed hypertable has no dimensions of its own , shares the original hypertable dims*/
	hypertable_insert(hypertable_id,
					  &schema_name,
					  &table_name,
					  &associated_schema_name,
					  NULL,
					  &chunk_sizing_info->func_schema,
					  &chunk_sizing_info->func_name,
					  chunk_sizing_info->target_size_bytes,
					  0 /*num_dimensions*/,
					  true);

	/* No indexes are created for the compressed hypertable here */

	/* Attach tablespace, if any */
	if (OidIsValid(tspc_oid))
	{
		NameData tspc_name;

		namestrcpy(&tspc_name, get_tablespace_name(tspc_oid));
		ts_tablespace_attach_internal(&tspc_name, table_relid, false);
	}

	insert_blocker_trigger_add(table_relid);
	/* lock will be released after the transaction is done */
	heap_close(rel, NoLock);
	return true;
}