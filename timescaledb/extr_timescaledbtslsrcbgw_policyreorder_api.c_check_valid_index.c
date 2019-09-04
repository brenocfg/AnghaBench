#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ indrelid; } ;
struct TYPE_5__ {int /*<<< orphan*/  schema_name; } ;
struct TYPE_6__ {scalar_t__ main_table_relid; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * Name ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_valid_index(Hypertable *ht, Name index_name)
{
	Oid index_oid;
	HeapTuple idxtuple;
	Form_pg_index indexForm;

	index_oid = get_relname_relid(NameStr(*index_name),
								  get_namespace_oid(NameStr(ht->fd.schema_name), false));
	idxtuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(index_oid));
	if (!HeapTupleIsValid(idxtuple))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("could not add reorder policy because the provided index is not a valid "
						"relation")));

	indexForm = (Form_pg_index) GETSTRUCT(idxtuple);
	if (indexForm->indrelid != ht->main_table_relid)
		elog(ERROR,
			 "could not add reorder policy because the provided index is not a valid index on the "
			 "hypertable");
	ReleaseSysCache(idxtuple);
}