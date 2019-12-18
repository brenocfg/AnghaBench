#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oidvector ;
struct TYPE_9__ {TYPE_2__* funcinfo; int /*<<< orphan*/  funcid; } ;
struct TYPE_8__ {int /*<<< orphan*/  nargs; int /*<<< orphan*/ * funcname; int /*<<< orphan*/  arg_types; scalar_t__ is_timescaledb_func; } ;
struct TYPE_7__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_2__ FuncInfo ;
typedef  TYPE_3__ FuncEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCNAMEARGSNSP ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _MAX_CACHE_FUNCTIONS ; 
 int /*<<< orphan*/ * buildoidvector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_hash ; 
 TYPE_2__* funcinfo ; 
 int /*<<< orphan*/  get_namespace_oid (char*,int) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 
 TYPE_3__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ts_extension_schema_name () ; 

__attribute__((used)) static void
initialize_func_info()
{
	HASHCTL hashctl = {
		.keysize = sizeof(Oid),
		.entrysize = sizeof(FuncEntry),
		.hcxt = CacheMemoryContext,
	};
	Oid extension_nsp = get_namespace_oid(ts_extension_schema_name(), false);
	Oid pg_nsp = get_namespace_oid("pg_catalog", false);
	HeapTuple tuple;
	Relation rel;
	int i;

	func_hash = hash_create("func_cache", _MAX_CACHE_FUNCTIONS, &hashctl, HASH_ELEM | HASH_BLOBS);

	rel = heap_open(ProcedureRelationId, AccessShareLock);

	for (i = 0; i < _MAX_CACHE_FUNCTIONS; i++)
	{
		FuncInfo *finfo = &funcinfo[i];
		Oid namespaceoid = finfo->is_timescaledb_func ? extension_nsp : pg_nsp;
		oidvector *paramtypes = buildoidvector(finfo->arg_types, finfo->nargs);
		FuncEntry *fentry;
		bool hash_found;
		Oid funcid;

		tuple = SearchSysCache3(PROCNAMEARGSNSP,
								PointerGetDatum(finfo->funcname),
								PointerGetDatum(paramtypes),
								ObjectIdGetDatum(namespaceoid));

		if (!HeapTupleIsValid(tuple))
			elog(ERROR,
				 "cache lookup failed for function \"%s\" with %d args",
				 finfo->funcname,
				 finfo->nargs);

		funcid = HeapTupleGetOid(tuple);

		fentry = hash_search(func_hash, &funcid, HASH_ENTER, &hash_found);
		Assert(!hash_found);
		fentry->funcid = funcid;
		fentry->funcinfo = finfo;
		ReleaseSysCache(tuple);
	}

	heap_close(rel, AccessShareLock);
}