#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ relowner; } ;
struct TYPE_4__ {int /*<<< orphan*/  main_table_relid; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_class ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (scalar_t__*,int*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (scalar_t__,int) ; 
 int /*<<< orphan*/  create_trigger_handler ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ts_trigger_create_all_on_chunk(Hypertable *ht, Chunk *chunk)
{
	int sec_ctx;
	Oid saved_uid;
	HeapTuple tuple;
	Form_pg_class form;

	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(ht->main_table_relid));

	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation ID %u", ht->main_table_relid);

	form = (Form_pg_class) GETSTRUCT(tuple);

	GetUserIdAndSecContext(&saved_uid, &sec_ctx);

	if (saved_uid != form->relowner)
		SetUserIdAndSecContext(form->relowner, sec_ctx | SECURITY_LOCAL_USERID_CHANGE);

	for_each_trigger(ht->main_table_relid, create_trigger_handler, chunk);

	if (saved_uid != form->relowner)
		SetUserIdAndSecContext(saved_uid, sec_ctx);

	ReleaseSysCache(tuple);
}