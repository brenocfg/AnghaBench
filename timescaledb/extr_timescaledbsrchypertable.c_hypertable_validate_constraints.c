#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ contype; scalar_t__ connoinherit; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hypertable_validate_constraints(Oid relid)
{
	Relation catalog;
	SysScanDesc scan;
	ScanKeyData scankey;
	HeapTuple tuple;

	catalog = heap_open(ConstraintRelationId, AccessShareLock);

	ScanKeyInit(&scankey,
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(relid));

	scan = systable_beginscan(catalog, ConstraintRelidTypidNameIndexId, true, NULL, 1, &scankey);

	while (HeapTupleIsValid(tuple = systable_getnext(scan)))
	{
		Form_pg_constraint form = (Form_pg_constraint) GETSTRUCT(tuple);

		if (form->contype == CONSTRAINT_CHECK && form->connoinherit)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
					 errmsg("cannot have NO INHERIT constraints on hypertable \"%s\"",
							get_rel_name(relid)),
					 errhint("Remove all NO INHERIT constraints from table \"%s\" before making it "
							 "a hypertable.",
							 get_rel_name(relid))));
	}

	systable_endscan(scan);
	heap_close(catalog, AccessShareLock);
}