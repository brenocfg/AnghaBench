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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ regproc ;
typedef  scalar_t__ (* proc_filter ) (TYPE_2__*,void*) ;
struct TYPE_10__ {int n_members; TYPE_1__** members; } ;
struct TYPE_9__ {scalar_t__ pronamespace; scalar_t__ prorettype; } ;
struct TYPE_8__ {int /*<<< orphan*/  tuple; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;
typedef  TYPE_4__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleGetOid (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupExplicitNamespace (char const*,int) ; 
 int /*<<< orphan*/  PROCNAMEARGSNSP ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_4__*) ; 
 TYPE_4__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
ts_lookup_proc_filtered(const char *schema, const char *funcname, Oid *rettype, proc_filter filter,
						void *filter_arg)
{
	Oid namespace_oid = LookupExplicitNamespace(schema, false);
	regproc func = InvalidOid;
	CatCList *catlist;
	int i;

	/*
	 * We could use SearchSysCache3 to get by (name, args, namespace), but
	 * that would not allow us to check for functions that take either
	 * ANYELEMENTOID or a dimension-specific in the same search.
	 */
	catlist = SearchSysCacheList1(PROCNAMEARGSNSP, CStringGetDatum(funcname));

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple proctup = &catlist->members[i]->tuple;
		Form_pg_proc procform = (Form_pg_proc) GETSTRUCT(proctup);

		if (procform->pronamespace == namespace_oid &&
			(filter == NULL || filter(procform, filter_arg)))
		{
			if (rettype)
				*rettype = procform->prorettype;

			func = HeapTupleGetOid(proctup);
			break;
		}
	}

	ReleaseSysCacheList(catlist);

	return func;
}