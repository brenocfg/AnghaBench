#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  schema_name; int /*<<< orphan*/  table_name; } ;
struct TYPE_26__ {TYPE_2__ fd; } ;
struct TYPE_25__ {char* tablespacename; int /*<<< orphan*/  options; int /*<<< orphan*/  inhRelations; int /*<<< orphan*/  relation; int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_24__ {int /*<<< orphan*/  main_table_relid; TYPE_1__ fd; } ;
struct TYPE_23__ {scalar_t__ objectId; } ;
struct TYPE_22__ {TYPE_3__* rd_rel; } ;
struct TYPE_21__ {scalar_t__ relowner; } ;
struct TYPE_18__ {scalar_t__ owner_uid; } ;
typedef  TYPE_4__* Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_5__ ObjectAddress ;
typedef  TYPE_6__ Hypertable ;
typedef  TYPE_7__ CreateStmt ;
typedef  TYPE_8__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 TYPE_5__ DefineRelation (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (scalar_t__*,int*) ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELKIND_RELATION ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (scalar_t__,int) ; 
 int /*<<< orphan*/  T_CreateStmt ; 
 int /*<<< orphan*/  create_toast_table (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  get_reloptions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeRangeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_attoptions (TYPE_4__*,scalar_t__) ; 
 TYPE_11__* ts_catalog_database_info_get () ; 

Oid
ts_chunk_create_table(Chunk *chunk, Hypertable *ht, char *tablespacename)
{
	Relation rel;
	ObjectAddress objaddr;
	int sec_ctx;
	CreateStmt stmt = {
		.type = T_CreateStmt,
		.relation = makeRangeVar(NameStr(chunk->fd.schema_name), NameStr(chunk->fd.table_name), 0),
		.inhRelations =
			list_make1(makeRangeVar(NameStr(ht->fd.schema_name), NameStr(ht->fd.table_name), 0)),
		.tablespacename = tablespacename,
		.options = get_reloptions(ht->main_table_relid),
	};
	Oid uid, saved_uid;

	rel = heap_open(ht->main_table_relid, AccessShareLock);

	/*
	 * If the chunk is created in the internal schema, become the catalog
	 * owner, otherwise become the hypertable owner
	 */
	if (namestrcmp(&chunk->fd.schema_name, INTERNAL_SCHEMA_NAME) == 0)
		uid = ts_catalog_database_info_get()->owner_uid;
	else
		uid = rel->rd_rel->relowner;

	GetUserIdAndSecContext(&saved_uid, &sec_ctx);

	if (uid != saved_uid)
		SetUserIdAndSecContext(uid, sec_ctx | SECURITY_LOCAL_USERID_CHANGE);

	objaddr = DefineRelation(&stmt,
							 RELKIND_RELATION,
							 rel->rd_rel->relowner,
							 NULL
#if !PG96
							 ,
							 NULL
#endif
	);

	/*
	 * need to create a toast table explicitly for some of the option setting
	 * to work
	 */
	create_toast_table(&stmt, objaddr.objectId);

	if (uid != saved_uid)
		SetUserIdAndSecContext(saved_uid, sec_ctx);

	set_attoptions(rel, objaddr.objectId);

	heap_close(rel, AccessShareLock);

	return objaddr.objectId;
}