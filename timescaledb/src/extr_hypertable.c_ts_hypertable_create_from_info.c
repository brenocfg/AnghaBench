#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_12__ {scalar_t__ target_size_bytes; int /*<<< orphan*/  func_name; int /*<<< orphan*/  func_schema; int /*<<< orphan*/  func; } ;
struct TYPE_11__ {int adaptive_chunking; int /*<<< orphan*/ * ht; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/ * Name ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_1__ DimensionInfo ;
typedef  TYPE_2__ ChunkSizingInfo ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ DIMENSION_INFO_IS_SET (TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_EXISTS ; 
 int /*<<< orphan*/  ERRCODE_WARNING ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int HYPERTABLE_CREATE_DISABLE_DEFAULT_INDEXES ; 
 int HYPERTABLE_CREATE_IF_NOT_EXISTS ; 
 int HYPERTABLE_CREATE_MIGRATE_DATA ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
#define  RELKIND_PARTITIONED_TABLE 129 
#define  RELKIND_RELATION 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_tablespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tablespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_check_associated_schema_permissions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_create_schema (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  hypertable_validate_constraints (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_blocker_trigger_add (int /*<<< orphan*/ ) ; 
 scalar_t__ is_inheritance_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int relation_has_tuples (int /*<<< orphan*/ ) ; 
 scalar_t__ table_has_replica_identity (int /*<<< orphan*/ ) ; 
 scalar_t__ table_has_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_is_logged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timescaledb_move_from_table_to_chunks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_adaptive_sizing_info_validate (TYPE_2__*) ; 
 TYPE_2__* ts_chunk_sizing_info_get_default_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_add_from_info (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_dimension_info_validate (TYPE_1__*) ; 
 void* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_indexing_create_default_indexes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_indexing_verify_indexes (int /*<<< orphan*/ *) ; 
 scalar_t__ ts_is_hypertable (int /*<<< orphan*/ ) ; 
 scalar_t__ ts_relation_has_transition_table_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_tablespace_attach_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool
ts_hypertable_create_from_info(Oid table_relid, int32 hypertable_id, uint32 flags,
							   DimensionInfo *time_dim_info, DimensionInfo *space_dim_info,
							   Name associated_schema_name, Name associated_table_prefix,
							   ChunkSizingInfo *chunk_sizing_info)
{
	Cache *hcache;
	Hypertable *ht;
	Oid associated_schema_oid;
	Oid user_oid = GetUserId();
	Oid tspc_oid = get_rel_tablespace(table_relid);
	bool table_has_data;
	NameData schema_name, table_name, default_associated_schema_name;
	Relation rel;
	bool if_not_exists = (flags & HYPERTABLE_CREATE_IF_NOT_EXISTS) != 0;

	/* quick exit in the easy if-not-exists case to avoid all locking */
	if (if_not_exists && ts_is_hypertable(table_relid))
	{
		ereport(NOTICE,
				(errcode(ERRCODE_TS_HYPERTABLE_EXISTS),
				 errmsg("table \"%s\" is already a hypertable, skipping",
						get_rel_name(table_relid))));

		return false;
	}

	/*
	 * Serialize hypertable creation to avoid having multiple transactions
	 * creating the same hypertable simultaneously. The lock should conflict
	 * with itself and RowExclusive, to prevent simultaneous inserts on the
	 * table. Also since TRUNCATE (part of data migrations) takes an
	 * AccessExclusiveLock take that lock level here too so that we don't have
	 * lock upgrades, which are susceptible to deadlocks. If we aren't
	 * migrating data, then shouldn't have much contention on the table thus
	 * not worth optimizing.
	 */
	rel = heap_open(table_relid, AccessExclusiveLock);

	/* recheck after getting lock */
	if (ts_is_hypertable(table_relid))
	{
		/*
		 * Unlock and return. Note that unlocking is analogous to what PG does
		 * for ALTER TABLE ADD COLUMN IF NOT EXIST
		 */
		heap_close(rel, AccessExclusiveLock);

		if (if_not_exists)
		{
			ereport(NOTICE,
					(errcode(ERRCODE_TS_HYPERTABLE_EXISTS),
					 errmsg("table \"%s\" is already a hypertable, skipping",
							get_rel_name(table_relid))));
			return false;
		}

		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_EXISTS),
				 errmsg("table \"%s\" is already a hypertable", get_rel_name(table_relid))));
	}

	/*
	 * Check that the user has permissions to make this table into a
	 * hypertable
	 */
	ts_hypertable_permissions_check(table_relid, user_oid);

	/* Is this the right kind of relation? */
	switch (get_rel_relkind(table_relid))
	{
#if PG10_GE
		case RELKIND_PARTITIONED_TABLE:
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("table \"%s\" is already partitioned", get_rel_name(table_relid)),
					 errdetail("It is not possible to turn partitioned tables into hypertables.")));
#endif
		case RELKIND_RELATION:
			break;
		default:
			ereport(ERROR, (errcode(ERRCODE_WRONG_OBJECT_TYPE), errmsg("invalid relation type")));
	}

	/* Check that the table doesn't have any unsupported constraints */
	hypertable_validate_constraints(table_relid);

	table_has_data = relation_has_tuples(rel);

	if ((flags & HYPERTABLE_CREATE_MIGRATE_DATA) == 0 && table_has_data)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("table \"%s\" is not empty", get_rel_name(table_relid)),
				 errhint("You can migrate data by specifying 'migrate_data => true' when calling "
						 "this function.")));

	if (is_inheritance_table(table_relid))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("table \"%s\" is already partitioned", get_rel_name(table_relid)),
				 errdetail(
					 "It is not possible to turn tables that use inheritance into hypertables.")));

	if (!table_is_logged(table_relid))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("table \"%s\" has to be logged", get_rel_name(table_relid)),
				 errdetail(
					 "It is not possible to turn temporary or unlogged tables into hypertables.")));

	if (table_has_replica_identity(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("table \"%s\" has replica identity set", get_rel_name(table_relid)),
				 errdetail("Logical replication is not supported on hypertables.")));

	if (table_has_rules(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("hypertables do not support rules"),
				 errdetail("Table \"%s\" has attached rules, which do not work on hypertables.",
						   get_rel_name(table_relid)),
				 errhint("Remove the rules before calling create_hypertable")));

	/*
	 * Create the associated schema where chunks are stored, or, check
	 * permissions if it already exists
	 */
	if (NULL == associated_schema_name)
	{
		namestrcpy(&default_associated_schema_name, INTERNAL_SCHEMA_NAME);
		associated_schema_name = &default_associated_schema_name;
	}

	associated_schema_oid =
		hypertable_check_associated_schema_permissions(NameStr(*associated_schema_name), user_oid);

	/* Create the associated schema if it doesn't already exist */
	if (!OidIsValid(associated_schema_oid))
		hypertable_create_schema(NameStr(*associated_schema_name));

	/*
	 * Hypertables do not support transition tables in triggers, so if the
	 * table already has such triggers we bail out
	 */
	if (ts_relation_has_transition_table_trigger(table_relid))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("hypertables do not support transition tables in triggers")));

	if (NULL == chunk_sizing_info)
		chunk_sizing_info = ts_chunk_sizing_info_get_default_disabled(table_relid);

	/* Validate and set chunk sizing information */
	if (OidIsValid(chunk_sizing_info->func))
	{
		ts_chunk_adaptive_sizing_info_validate(chunk_sizing_info);

		if (chunk_sizing_info->target_size_bytes > 0)
		{
			ereport(NOTICE,
					(errcode(ERRCODE_WARNING),
					 errmsg("adaptive chunking is a BETA feature and is not recommended for "
							"production deployments")));

			time_dim_info->adaptive_chunking = true;
		}
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid chunk_sizing function: cannot be NULL")));
	}

	/* Validate that the dimensions are OK */
	ts_dimension_info_validate(time_dim_info);

	if (DIMENSION_INFO_IS_SET(space_dim_info))
		ts_dimension_info_validate(space_dim_info);

	/* Checks pass, now we can create the catalog information */
	namestrcpy(&schema_name, get_namespace_name(get_rel_namespace(table_relid)));
	namestrcpy(&table_name, get_rel_name(table_relid));

	hypertable_insert(hypertable_id,
					  &schema_name,
					  &table_name,
					  associated_schema_name,
					  associated_table_prefix,
					  &chunk_sizing_info->func_schema,
					  &chunk_sizing_info->func_name,
					  chunk_sizing_info->target_size_bytes,
					  DIMENSION_INFO_IS_SET(space_dim_info) ? 2 : 1,
					  false);

	/* Get the a Hypertable object via the cache */
	hcache = ts_hypertable_cache_pin();
	time_dim_info->ht = ts_hypertable_cache_get_entry(hcache, table_relid);

	Assert(time_dim_info->ht != NULL);

	/* Add validated dimensions */
	ts_dimension_add_from_info(time_dim_info);

	if (DIMENSION_INFO_IS_SET(space_dim_info))
	{
		space_dim_info->ht = time_dim_info->ht;
		ts_dimension_add_from_info(space_dim_info);
	}

	/* Refresh the cache to get the updated hypertable with added dimensions */
	ts_cache_release(hcache);
	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, table_relid);

	Assert(ht != NULL);

	/* Verify that existing indexes are compatible with a hypertable */
	ts_indexing_verify_indexes(ht);

	/* Attach tablespace, if any */
	if (OidIsValid(tspc_oid))
	{
		NameData tspc_name;

		namestrcpy(&tspc_name, get_tablespace_name(tspc_oid));
		ts_tablespace_attach_internal(&tspc_name, table_relid, false);
	}

	/*
	 * Migrate data from the main table to chunks
	 *
	 * Note: we do not unlock here. We wait till the end of the txn instead.
	 * Must close the relation before migrating data.
	 */
	heap_close(rel, NoLock);

	if (table_has_data)
	{
		ereport(NOTICE,
				(errmsg("migrating data to chunks"),
				 errdetail("Migration might take a while depending on the amount of data.")));

		timescaledb_move_from_table_to_chunks(ht, AccessShareLock);
	}

	insert_blocker_trigger_add(table_relid);

	if ((flags & HYPERTABLE_CREATE_DISABLE_DEFAULT_INDEXES) == 0)
		ts_indexing_create_default_indexes(ht);

	ts_cache_release(hcache);

	return true;
}