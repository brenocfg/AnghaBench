#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  indisclustered; } ;
struct TYPE_11__ {TYPE_1__* rd_rel; } ;
struct TYPE_10__ {scalar_t__ relpersistence; scalar_t__ relkind; scalar_t__ relhasoids; scalar_t__ relisshared; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CheckTableNotInUse (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ERRCODE_ASSERT_FAILURE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WARNING ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 scalar_t__ IsSystemRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RELOID ; 
 scalar_t__ RELPERSISTENCE_PERMANENT ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  check_index_is_clusterable (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_class_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timescale_rebuild_relation (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* try_relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
timescale_reorder_rel(Oid tableOid, Oid indexOid, bool verbose, Oid wait_id,
					  Oid destination_tablespace, Oid index_tablespace)
{
	Relation OldHeap;
	HeapTuple tuple;
	Form_pg_index indexForm;

	if (!OidIsValid(indexOid))
		elog(ERROR, "Reorder must specify an index.");

	/* Check for user-requested abort. */
	CHECK_FOR_INTERRUPTS();

	/*
	 * We grab exclusive access to the target rel and index for the duration
	 * of the transaction.  (This is redundant for the single-transaction
	 * case, since cluster() already did it.)  The index lock is taken inside
	 * check_index_is_clusterable.
	 */
	OldHeap = try_relation_open(tableOid, ExclusiveLock);

	/* If the table has gone away, we can skip processing it */
	if (!OldHeap)
	{
		ereport(WARNING, (errcode(ERRCODE_WARNING), errmsg("table disappeared during reorder.")));
		return;
	}

	/*
	 * Since we may open a new transaction for each relation, we have to check
	 * that the relation still is what we think it is.
	 */
	/* Check that the user still owns the relation */
	if (!pg_class_ownercheck(tableOid, GetUserId()))
	{
		relation_close(OldHeap, ExclusiveLock);
		ereport(WARNING, (errcode(ERRCODE_WARNING), errmsg("ownership change during reorder.")));
		return;
	}

	if (IsSystemRelation(OldHeap))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot reorder a system relation.")));

	if (OldHeap->rd_rel->relpersistence != RELPERSISTENCE_PERMANENT)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("can only reorder a permanent table.")));

	/* We do not allow reordering on shared catalogs. */
	if (OldHeap->rd_rel->relisshared)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot reorder a shared catalog")));

	if (OldHeap->rd_rel->relkind != RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("can only reorder a relation.")));

	if (OldHeap->rd_rel->relhasoids)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot reorder a table with OIDs.")));

	/*
	 * Check that the index still exists
	 */
	if (!SearchSysCacheExists1(RELOID, ObjectIdGetDatum(indexOid)))
	{
		ereport(WARNING, (errcode(ERRCODE_WARNING), errmsg("index disappeared during reorder")));
		relation_close(OldHeap, ExclusiveLock);
		return;
	}

	/*
	 * Check that the index is still the one with indisclustered set.
	 */
	tuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexOid));
	if (!HeapTupleIsValid(tuple)) /* probably can't happen */
	{
		ereport(WARNING, (errcode(ERRCODE_WARNING), errmsg("invalid index heap during reorder")));
		relation_close(OldHeap, ExclusiveLock);
		return;
	}
	indexForm = (Form_pg_index) GETSTRUCT(tuple);

	/*
	 * We always mark indexes as clustered when we intercept a cluster
	 * command, if it's not marked as such here, something has gone wrong
	 */
	if (!indexForm->indisclustered)
		ereport(ERROR,
				(errcode(ERRCODE_ASSERT_FAILURE), errmsg("invalid index heap during reorder")));
	ReleaseSysCache(tuple);

	/*
	 * Also check for active uses of the relation in the current transaction,
	 * including open scans and pending AFTER trigger events.
	 */
	CheckTableNotInUse(OldHeap, "CLUSTER");

	/* Check heap and index are valid to cluster on */
	check_index_is_clusterable(OldHeap, indexOid, true, ExclusiveLock);

	/* timescale_rebuild_relation does all the dirty work */
	timescale_rebuild_relation(OldHeap,
							   indexOid,
							   verbose,
							   wait_id,
							   destination_tablespace,
							   index_tablespace);

	/* NB: timescale_rebuild_relation does heap_close() on OldHeap */
}