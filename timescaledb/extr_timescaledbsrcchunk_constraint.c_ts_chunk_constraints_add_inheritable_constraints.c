#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  conname; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  ChunkConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chunk_constraint_need_on_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_constraints_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

int
ts_chunk_constraints_add_inheritable_constraints(ChunkConstraints *ccs, int32 chunk_id,
												 Oid hypertable_oid)
{
	ScanKeyData skey;
	Relation rel;
	SysScanDesc scan;
	HeapTuple htup;
	int num_added = 0;

	ScanKeyInit(&skey, Anum_pg_constraint_conrelid, BTEqualStrategyNumber, F_OIDEQ, hypertable_oid);

	rel = heap_open(ConstraintRelationId, AccessShareLock);
	scan = systable_beginscan(rel, ConstraintRelidTypidNameIndexId, true, NULL, 1, &skey);

	while (HeapTupleIsValid(htup = systable_getnext(scan)))
	{
		Form_pg_constraint pg_constraint = (Form_pg_constraint) GETSTRUCT(htup);

		if (chunk_constraint_need_on_chunk(pg_constraint))
		{
			chunk_constraints_add(ccs, chunk_id, 0, NULL, NameStr(pg_constraint->conname));
			num_added++;
		}
	}

	systable_endscan(scan);
	heap_close(rel, AccessShareLock);

	return num_added;
}