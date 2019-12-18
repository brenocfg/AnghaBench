#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OPERNAMENSP ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
ts_get_operator(const char *name, Oid namespace, Oid left, Oid right)
{
	HeapTuple tup;
	Oid opoid = InvalidOid;

	tup = SearchSysCache4(OPERNAMENSP,
						  PointerGetDatum(name),
						  ObjectIdGetDatum(left),
						  ObjectIdGetDatum(right),
						  ObjectIdGetDatum(namespace));
	if (HeapTupleIsValid(tup))
	{
		opoid = HeapTupleGetOid(tup);
		ReleaseSysCache(tup);
	}

	return opoid;
}