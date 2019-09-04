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
struct TYPE_2__ {int /*<<< orphan*/  typname; int /*<<< orphan*/  typnamespace; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
polydatum_serialize_type(StringInfo buf, Oid type_oid)
{
	HeapTuple tup;
	Form_pg_type type_tuple;
	char *namespace_name;

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(type_oid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", type_oid);
	type_tuple = (Form_pg_type) GETSTRUCT(tup);
	namespace_name = get_namespace_name(type_tuple->typnamespace);

	/* send qualified type name */
	pq_sendstring(buf, namespace_name);
	pq_sendstring(buf, NameStr(type_tuple->typname));

	ReleaseSysCache(tup);
}