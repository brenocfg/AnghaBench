#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* rd_rel; } ;
struct TYPE_7__ {scalar_t__ relpersistence; int /*<<< orphan*/  reltoastrelid; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckTableForSerializableConflictIn (TYPE_2__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetOldestMultiXactId () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REINDEX_REL_PROCESS_TOAST ; 
 scalar_t__ RELPERSISTENCE_UNLOGGED ; 
 int /*<<< orphan*/  RecentXmin ; 
 int /*<<< orphan*/  RelationSetNewRelfilenode (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_truncate_find_FKs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1_oid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reindex_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
truncate_relation(Oid table_oid)
{
	List *fks = heap_truncate_find_FKs(list_make1_oid(table_oid));
	/* Take an access exclusive lock now. Note that this may very well
	 *  be a lock upgrade. */
	Relation rel = relation_open(table_oid, AccessExclusiveLock);
	MultiXactId minmulti;
	Oid toast_relid;

	/* Chunks should never have fks into them, but double check */
	if (fks != NIL)
		elog(ERROR, "found a FK into a chunk while truncating");

	CheckTableForSerializableConflictIn(rel);

	minmulti = GetOldestMultiXactId();

	RelationSetNewRelfilenode(rel, rel->rd_rel->relpersistence, RecentXmin, minmulti);

	toast_relid = rel->rd_rel->reltoastrelid;

	heap_close(rel, NoLock);

	if (OidIsValid(toast_relid))
	{
		rel = relation_open(toast_relid, AccessExclusiveLock);
		RelationSetNewRelfilenode(rel, rel->rd_rel->relpersistence, RecentXmin, minmulti);
		Assert(rel->rd_rel->relpersistence != RELPERSISTENCE_UNLOGGED);
		heap_close(rel, NoLock);
	}

	reindex_relation(table_oid, REINDEX_REL_PROCESS_TOAST, 0);
}