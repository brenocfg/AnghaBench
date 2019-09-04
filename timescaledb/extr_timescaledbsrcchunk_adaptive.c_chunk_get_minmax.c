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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  scalar_t__ MinMaxResult ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 scalar_t__ MINMAX_FOUND ; 
 scalar_t__ MINMAX_NO_INDEX ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_attname_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ minmax_heapscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ relation_minmax_indexscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
chunk_get_minmax(Oid relid, Oid atttype, AttrNumber attnum, Datum minmax[2])
{
	Relation rel = heap_open(relid, AccessShareLock);
	NameData attname;
	MinMaxResult res;

	namestrcpy(&attname, get_attname_compat(relid, attnum, false));
	res = relation_minmax_indexscan(rel, atttype, &attname, attnum, minmax);

	if (res == MINMAX_NO_INDEX)
	{
		ereport(WARNING,
				(errmsg("no index on \"%s\" found for adaptive chunking on chunk \"%s\"",
						NameStr(attname),
						get_rel_name(relid)),
				 errdetail("Adaptive chunking works best with an index on the dimension being "
						   "adapted.")));

		res = minmax_heapscan(rel, atttype, attnum, minmax);
	}

	heap_close(rel, AccessShareLock);

	return res == MINMAX_FOUND;
}