#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* int32 ;
typedef  int /*<<< orphan*/  float4 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_16__ {long relfilenode; long reltablespace; char relpersistence; long reltoastrelid; scalar_t__ relkind; void* relallvisible; int /*<<< orphan*/  reltuples; void* relpages; int /*<<< orphan*/  relminmxid; int /*<<< orphan*/  relfrozenxid; int /*<<< orphan*/  relname; } ;
struct TYPE_15__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_14__ {long objectId; scalar_t__ objectSubId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  long Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_class ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogIndexInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogOpenIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdateWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidMultiXactId ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHookArg (void*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IsSystemClass (long,TYPE_3__*) ; 
 int MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 long NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (long) ; 
 int /*<<< orphan*/  OidIsValid (long) ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_TOASTVALUE ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationCloseSmgrByOid (long) ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 long deleteDependencyRecordsFor (void*,long,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_heap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 long toast_get_valid_index (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swap_relation_files(Oid r1, Oid r2, bool swap_toast_by_content, bool is_internal,
					TransactionId frozenXid, MultiXactId cutoffMulti)
{
	Relation relRelation;
	HeapTuple reltup1, reltup2;
	Form_pg_class relform1, relform2;
	Oid relfilenode1, relfilenode2;
	Oid swaptemp;
	char swptmpchr;

	/* We need writable copies of both pg_class tuples. */
	relRelation = heap_open(RelationRelationId, RowExclusiveLock);

	reltup1 = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(r1));
	if (!HeapTupleIsValid(reltup1))
		elog(ERROR, "cache lookup failed for relation %u", r1);
	relform1 = (Form_pg_class) GETSTRUCT(reltup1);

	reltup2 = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(r2));
	if (!HeapTupleIsValid(reltup2))
		elog(ERROR, "cache lookup failed for relation %u", r2);
	relform2 = (Form_pg_class) GETSTRUCT(reltup2);

	relfilenode1 = relform1->relfilenode;
	relfilenode2 = relform2->relfilenode;

	if (!OidIsValid(relfilenode1) || !OidIsValid(relfilenode2))
		elog(ERROR, "cannot reorder mapped relation \"%s\".", NameStr(relform1->relname));

	/* swap relfilenodes, reltablespaces, relpersistence */

	swaptemp = relform1->relfilenode;
	relform1->relfilenode = relform2->relfilenode;
	relform2->relfilenode = swaptemp;

	swaptemp = relform1->reltablespace;
	relform1->reltablespace = relform2->reltablespace;
	relform2->reltablespace = swaptemp;

	swptmpchr = relform1->relpersistence;
	relform1->relpersistence = relform2->relpersistence;
	relform2->relpersistence = swptmpchr;

	/* Also swap toast links, if we're swapping by links */
	if (!swap_toast_by_content)
	{
		swaptemp = relform1->reltoastrelid;
		relform1->reltoastrelid = relform2->reltoastrelid;
		relform2->reltoastrelid = swaptemp;
	}

	/* set rel1's frozen Xid and minimum MultiXid */
	if (relform1->relkind != RELKIND_INDEX)
	{
		Assert(TransactionIdIsNormal(frozenXid));
		relform1->relfrozenxid = frozenXid;
		Assert(MultiXactIdIsValid(cutoffMulti));
		relform1->relminmxid = cutoffMulti;
	}

	/* swap size statistics too, since new rel has freshly-updated stats */
	{
		int32 swap_pages;
		float4 swap_tuples;
		int32 swap_allvisible;

		swap_pages = relform1->relpages;
		relform1->relpages = relform2->relpages;
		relform2->relpages = swap_pages;

		swap_tuples = relform1->reltuples;
		relform1->reltuples = relform2->reltuples;
		relform2->reltuples = swap_tuples;

		swap_allvisible = relform1->relallvisible;
		relform1->relallvisible = relform2->relallvisible;
		relform2->relallvisible = swap_allvisible;
	}

	/* Update the tuples in pg_class. */
	{
		CatalogIndexState indstate;
#if PG96
		simple_heap_update(relRelation, &reltup1->t_self, reltup1);
		simple_heap_update(relRelation, &reltup2->t_self, reltup2);

		/* Keep system catalogs current */
		indstate = CatalogOpenIndexes(relRelation);
		CatalogIndexInsert(indstate, reltup1);
		CatalogIndexInsert(indstate, reltup2);
		CatalogCloseIndexes(indstate);
#else
		indstate = CatalogOpenIndexes(relRelation);
		CatalogTupleUpdateWithInfo(relRelation, &reltup1->t_self, reltup1, indstate);
		CatalogTupleUpdateWithInfo(relRelation, &reltup2->t_self, reltup2, indstate);
		CatalogCloseIndexes(indstate);
#endif
	}

	/*
	 * Post alter hook for modified relations. The change to r2 is always
	 * internal, but r1 depends on the invocation context.
	 */
	InvokeObjectPostAlterHookArg(RelationRelationId, r1, 0, InvalidOid, is_internal);
	InvokeObjectPostAlterHookArg(RelationRelationId, r2, 0, InvalidOid, true);

	/*
	 * If we have toast tables associated with the relations being swapped,
	 * deal with them too.
	 */
	if (relform1->reltoastrelid || relform2->reltoastrelid)
	{
		if (swap_toast_by_content)
		{
			if (relform1->reltoastrelid && relform2->reltoastrelid)
			{
				/* Recursively swap the contents of the toast tables */
				swap_relation_files(relform1->reltoastrelid,
									relform2->reltoastrelid,
									swap_toast_by_content,
									is_internal,
									frozenXid,
									cutoffMulti);
			}
			else
			{
				/* caller messed up */
				elog(ERROR, "cannot swap toast files by content when there's only one");
			}
		}
		else
		{
			/*
			 * We swapped the ownership links, so we need to change dependency
			 * data to match.
			 *
			 * NOTE: it is possible that only one table has a toast table.
			 *
			 * NOTE: at present, a TOAST table's only dependency is the one on
			 * its owning table.  If more are ever created, we'd need to use
			 * something more selective than deleteDependencyRecordsFor() to
			 * get rid of just the link we want.
			 */
			ObjectAddress baseobject, toastobject;
			long count;

			/*
			 * The original code disallowed this case for system catalogs. We
			 * don't allow reordering system catalogs, but Assert anyway
			 */
			Assert(!IsSystemClass(r1, relform1));

			/* Delete old dependencies */
			if (relform1->reltoastrelid)
			{
				count =
					deleteDependencyRecordsFor(RelationRelationId, relform1->reltoastrelid, false);
				if (count != 1)
					elog(ERROR, "expected one dependency record for TOAST table, found %ld", count);
			}
			if (relform2->reltoastrelid)
			{
				count =
					deleteDependencyRecordsFor(RelationRelationId, relform2->reltoastrelid, false);
				if (count != 1)
					elog(ERROR, "expected one dependency record for TOAST table, found %ld", count);
			}

			/* Register new dependencies */
			baseobject.classId = RelationRelationId;
			baseobject.objectSubId = 0;
			toastobject.classId = RelationRelationId;
			toastobject.objectSubId = 0;

			if (relform1->reltoastrelid)
			{
				baseobject.objectId = r1;
				toastobject.objectId = relform1->reltoastrelid;
				recordDependencyOn(&toastobject, &baseobject, DEPENDENCY_INTERNAL);
			}

			if (relform2->reltoastrelid)
			{
				baseobject.objectId = r2;
				toastobject.objectId = relform2->reltoastrelid;
				recordDependencyOn(&toastobject, &baseobject, DEPENDENCY_INTERNAL);
			}
		}
	}

	/*
	 * If we're swapping two toast tables by content, do the same for their
	 * valid index. The swap can actually be safely done only if the relations
	 * have indexes.
	 */
	if (swap_toast_by_content && relform1->relkind == RELKIND_TOASTVALUE &&
		relform2->relkind == RELKIND_TOASTVALUE)
	{
		Oid toastIndex1, toastIndex2;

		/* Get valid index for each relation */
		toastIndex1 = toast_get_valid_index(r1, AccessExclusiveLock);
		toastIndex2 = toast_get_valid_index(r2, AccessExclusiveLock);

		swap_relation_files(toastIndex1,
							toastIndex2,
							swap_toast_by_content,
							is_internal,
							InvalidTransactionId,
							InvalidMultiXactId);
	}

	/* Clean up. */
	heap_freetuple(reltup1);
	heap_freetuple(reltup2);

	heap_close(relRelation, RowExclusiveLock);

	/*
	 * Close both relcache entries' smgr links.  We need this kludge because
	 * both links will be invalidated during upcoming CommandCounterIncrement.
	 * Whichever of the rels is the second to be cleared will have a dangling
	 * reference to the other's smgr entry.  Rather than trying to avoid this
	 * by ordering operations just so, it's easiest to close the links first.
	 * (Fortunately, since one of the entries is local in our transaction,
	 * it's sufficient to clear out our own relcache this way; the problem
	 * cannot arise for other backends when they see our update on the
	 * non-transient relation.)
	 *
	 * Caution: the placement of this step interacts with the decision to
	 * handle toast rels by recursion.  When we are trying to rebuild pg_class
	 * itself, the smgr close on pg_class must happen after all accesses in
	 * this function.
	 */
	RelationCloseSmgrByOid(r1);
	RelationCloseSmgrByOid(r2);
}