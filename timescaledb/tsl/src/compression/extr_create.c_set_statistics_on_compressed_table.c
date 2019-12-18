#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_16__ {scalar_t__ type_oid; } ;
struct TYPE_15__ {scalar_t__ attnum; scalar_t__ atttypid; int attstattarget; int /*<<< orphan*/  attname; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_13__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_attribute ;

/* Variables and functions */
 scalar_t__ AttributeRelationId ; 
 int /*<<< orphan*/  CUSTOM_TYPE_COMPRESSED_DATA ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationClose (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopyAttName (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int /*<<< orphan*/  relation_open (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* ts_custom_type_cache_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_statistics_on_compressed_table(Oid compressed_table_id)
{
	Relation table_rel = relation_open(compressed_table_id, ShareUpdateExclusiveLock);
	Relation attrelation = relation_open(AttributeRelationId, RowExclusiveLock);
	TupleDesc table_desc = RelationGetDescr(table_rel);
	Oid compressed_data_type = ts_custom_type_cache_get(CUSTOM_TYPE_COMPRESSED_DATA)->type_oid;
	for (int i = 0; i < table_desc->natts; i++)
	{
		Form_pg_attribute attrtuple;
		HeapTuple tuple;
		Form_pg_attribute col_attr = TupleDescAttr(table_desc, i);

		/* skip system columns */
		if (col_attr->attnum <= 0)
			continue;

		tuple = SearchSysCacheCopyAttName(compressed_table_id, NameStr(col_attr->attname));

		if (!HeapTupleIsValid(tuple))
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_COLUMN),
					 errmsg("column \"%s\" of compressed table \"%s\" does not exist",
							NameStr(col_attr->attname),
							RelationGetRelationName(table_rel))));

		attrtuple = (Form_pg_attribute) GETSTRUCT(tuple);

		/* the planner should never look at compressed column statistics because
		 * it will not understand them. Statistics on the other columns,
		 * segmentbys and metadata, are very important, so we increase their
		 * target.
		 */
		if (col_attr->atttypid == compressed_data_type)
			attrtuple->attstattarget = 0;
		else
			attrtuple->attstattarget = 1000;

		CatalogTupleUpdate(attrelation, &tuple->t_self, tuple);

		InvokeObjectPostAlterHook(RelationRelationId, compressed_table_id, attrtuple->attnum);
		heap_freetuple(tuple);
	}

	RelationClose(attrelation);
	RelationClose(table_rel);
}