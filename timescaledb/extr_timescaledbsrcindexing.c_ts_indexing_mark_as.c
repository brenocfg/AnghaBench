#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int indisvalid; int indisclustered; int /*<<< orphan*/  indisready; int /*<<< orphan*/  indislive; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int IndexValidity ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  INDEXRELID ; 
#define  IndexInvalid 129 
 int /*<<< orphan*/  IndexRelationId ; 
#define  IndexValid 128 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_copytuple (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ts_indexing_mark_as(Oid index_id, IndexValidity validity)
{
	Relation pg_index;
	HeapTuple indexTuple;
	HeapTuple new_tuple;
	Form_pg_index indexForm;
	bool was_valid;

	/* Open pg_index and fetch a writable copy of the index's tuple */
	pg_index = heap_open(IndexRelationId, RowExclusiveLock);

	indexTuple = SearchSysCacheCopy1(INDEXRELID, ObjectIdGetDatum(index_id));

	if (!HeapTupleIsValid(indexTuple))
		elog(ERROR, "cache lookup failed when marking index %u", index_id);

	new_tuple = heap_copytuple(indexTuple);
	indexForm = (Form_pg_index) GETSTRUCT(new_tuple);

	was_valid = indexForm->indisvalid;

	/* Perform the requested state change on the copy */
	switch (validity)
	{
		case IndexValid:
			Assert(indexForm->indislive);
			Assert(indexForm->indisready);
			indexForm->indisvalid = true;
			break;
		case IndexInvalid:
			indexForm->indisvalid = false;
			indexForm->indisclustered = false;
			break;
	}

	/* ... and write it back */
	CatalogTupleUpdate(pg_index, &indexTuple->t_self, new_tuple);

	heap_close(pg_index, RowExclusiveLock);
	return was_valid;
}