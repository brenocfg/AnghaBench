#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int16 ;
struct TYPE_10__ {TYPE_1__* col_meta; } ;
struct TYPE_9__ {scalar_t__ contype; int /*<<< orphan*/  conname; } ;
struct TYPE_8__ {int /*<<< orphan*/  main_table_relid; } ;
struct TYPE_7__ {int segmentby_column_index; int orderby_column_index; int /*<<< orphan*/  attname; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Name ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ CompressColInfo ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conkey ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 scalar_t__ CONSTRAINT_EXCLUSION ; 
 scalar_t__ CONSTRAINT_FOREIGN ; 
 scalar_t__ CONSTRAINT_TRIGGER ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ INT2OID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namecpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  palloc0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
validate_existing_constraints(Hypertable *ht, CompressColInfo *colinfo)
{
	Oid relid = ht->main_table_relid;
	Relation pg_constr;
	SysScanDesc scan;
	ScanKeyData scankey;
	HeapTuple tuple;
	List *conlist = NIL;
	ArrayType *arr;

	pg_constr = heap_open(ConstraintRelationId, AccessShareLock);

	ScanKeyInit(&scankey,
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(relid));

	scan = systable_beginscan(pg_constr, ConstraintRelidTypidNameIndexId, true, NULL, 1, &scankey);
	while (HeapTupleIsValid(tuple = systable_getnext(scan)))
	{
		Form_pg_constraint form = (Form_pg_constraint) GETSTRUCT(tuple);

		/* we check primary ,unique and exclusion constraints.
		 * move foreign key constarints over to compression table
		 * ignore triggers
		 */
		if (form->contype == CONSTRAINT_CHECK || form->contype == CONSTRAINT_TRIGGER)
			continue;
		else if (form->contype == CONSTRAINT_EXCLUSION)
		{
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("constraint %s is not supported for compression",
							NameStr(form->conname)),
					 errhint("Exclusion constraints are not supported on hypertables that are "
							 "compressed.")));
		}
		else
		{
			int j, numkeys;
			int16 *attnums;
			bool isNull;
			/* Extract the conkey array, ie, attnums of PK's columns */
			Datum adatum = heap_getattr(tuple,
										Anum_pg_constraint_conkey,
										RelationGetDescr(pg_constr),
										&isNull);
			if (isNull)
				elog(ERROR, "null conkey for constraint %u", HeapTupleGetOid(tuple));
			arr = DatumGetArrayTypeP(adatum); /* ensure not toasted */
			numkeys = ARR_DIMS(arr)[0];
			if (ARR_NDIM(arr) != 1 || numkeys < 0 || ARR_HASNULL(arr) ||
				ARR_ELEMTYPE(arr) != INT2OID)
				elog(ERROR, "conkey is not a 1-D smallint array");
			attnums = (int16 *) ARR_DATA_PTR(arr);
			for (j = 0; j < numkeys; j++)
			{
				int16 colno = attnums[j] - 1;
				if (form->contype == CONSTRAINT_FOREIGN)
				{
					/* is this a segment-by column */
					if (colinfo->col_meta[colno].segmentby_column_index < 1)
					{
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("constraint %s requires column %s to be a segment_by "
										"column for compression",
										NameStr(form->conname),
										NameStr(colinfo->col_meta[colno].attname)),
								 errhint("Only segment by columns can be used in foreign key"
										 "constraints on hypertables that are compressed.")));
					}
					else
					{
						Name conname = palloc0(NAMEDATALEN);
						namecpy(conname, &form->conname);
						conlist = lappend(conlist, conname);
					}
				}
				else
				{
					/* is colno  a segment-by or order_by column */
					if (colinfo->col_meta[colno].segmentby_column_index < 1 &&
						colinfo->col_meta[colno].orderby_column_index < 1)
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("constraint %s requires column %s to be a segment_by or "
										"order_by column for compression",
										NameStr(form->conname),
										NameStr(colinfo->col_meta[colno].attname)),
								 errhint("Only segment by and order by columns can be used in "
										 "constraints on hypertables that are compressed.")));
				}
			}
		}
	}

	systable_endscan(scan);
	heap_close(pg_constr, AccessShareLock);
	return conlist;
}