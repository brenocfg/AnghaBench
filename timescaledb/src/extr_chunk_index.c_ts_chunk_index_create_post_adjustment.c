#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  values; } ;
typedef  TYPE_3__ oidvector ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  bits16 ;
struct TYPE_15__ {int /*<<< orphan*/  rd_indoption; int /*<<< orphan*/  rd_indcollation; TYPE_2__* rd_rel; TYPE_1__* rd_index; int /*<<< orphan*/  rd_indextuple; } ;
struct TYPE_13__ {int /*<<< orphan*/  relam; } ;
struct TYPE_12__ {scalar_t__ indisprimary; } ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_reloptions ; 
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  INDEX_CREATE_ADD_CONSTRAINT ; 
 int /*<<< orphan*/  INDEX_CREATE_IS_PRIMARY ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* chunk_index_choose_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_index_colnames (TYPE_4__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_create_compat (TYPE_4__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ts_chunk_index_get_tablespace (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 

__attribute__((used)) static Oid
ts_chunk_index_create_post_adjustment(int32 hypertable_id, Relation template_indexrel,
									  Relation chunkrel, IndexInfo *indexinfo, bool isconstraint,
									  Oid index_tablespace)
{
	Oid chunk_indexrelid = InvalidOid;
	const char *indexname;
	HeapTuple tuple;
	bool isnull;
	Datum reloptions;
	Datum indclass;
	oidvector *indclassoid;
	List *colnames = create_index_colnames(template_indexrel);
	Oid tablespace;
	bits16 flags = 0;

	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(RelationGetRelid(template_indexrel)));

	if (!HeapTupleIsValid(tuple))
		elog(ERROR,
			 "cache lookup failed for index relation %u",
			 RelationGetRelid(template_indexrel));

	reloptions = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_reloptions, &isnull);

	indclass = SysCacheGetAttr(INDEXRELID,
							   template_indexrel->rd_indextuple,
							   Anum_pg_index_indclass,
							   &isnull);
	Assert(!isnull);
	indclassoid = (oidvector *) DatumGetPointer(indclass);

	indexname = chunk_index_choose_name(get_rel_name(RelationGetRelid(chunkrel)),
										get_rel_name(RelationGetRelid(template_indexrel)),
										get_rel_namespace(RelationGetRelid(chunkrel)));
	if (OidIsValid(index_tablespace))
		tablespace = index_tablespace;
	else
		tablespace = ts_chunk_index_get_tablespace(hypertable_id, template_indexrel, chunkrel);

	/* assign flags for index creation and constraint creation */
	if (isconstraint)
		flags |= INDEX_CREATE_ADD_CONSTRAINT;
	if (template_indexrel->rd_index->indisprimary)
		flags |= INDEX_CREATE_IS_PRIMARY;

	chunk_indexrelid = index_create_compat(chunkrel,
										   indexname,
										   InvalidOid,
										   InvalidOid,
										   indexinfo,
										   colnames,
										   template_indexrel->rd_rel->relam,
										   tablespace,
										   template_indexrel->rd_indcollation,
										   indclassoid->values,
										   template_indexrel->rd_indoption,
										   reloptions,
										   flags,
										   0,	  /* constr_flags constant and 0
													* for now */
										   false,  /* allow system table mods */
										   false); /* is internal */

	ReleaseSysCache(tuple);

	return chunk_indexrelid;
}