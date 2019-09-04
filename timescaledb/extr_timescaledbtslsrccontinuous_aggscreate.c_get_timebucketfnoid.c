#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n_members; TYPE_1__** members; } ;
struct TYPE_5__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCNAMEARGSNSP ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_2__*) ; 
 TYPE_2__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TIMEBUCKETFN ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
get_timebucketfnoid()
{
	List *retlist = NIL;
	Oid funcoid;
	const char *funcname = TIMEBUCKETFN;
	CatCList *catlist = SearchSysCacheList1(PROCNAMEARGSNSP, CStringGetDatum(funcname));
	int i;

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple proctup = &catlist->members[i]->tuple;
		funcoid = ObjectIdGetDatum(HeapTupleGetOid(proctup));
		retlist = lappend_oid(retlist, funcoid);
	}
	ReleaseSysCacheList(catlist);
	Assert(retlist != NIL);
	return retlist;
}