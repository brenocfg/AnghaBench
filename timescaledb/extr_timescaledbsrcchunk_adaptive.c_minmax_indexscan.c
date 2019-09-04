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
typedef  int /*<<< orphan*/  MinMaxResult ;
typedef  int /*<<< orphan*/  IndexScanDesc ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BackwardScanDirection ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINMAX_FOUND ; 
 int /*<<< orphan*/  MINMAX_NO_TUPLES ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MinMaxResult
minmax_indexscan(Relation rel, Relation idxrel, AttrNumber attnum, Datum minmax[2])
{
	IndexScanDesc scan = index_beginscan(rel, idxrel, GetTransactionSnapshot(), 0, 0);
	HeapTuple tuple;
	bool isnull;
	bool nulls[2] = { true, true };
	int n = 0;

	tuple = index_getnext(scan, BackwardScanDirection);

	if (HeapTupleIsValid(tuple))
	{
		minmax[n] = heap_getattr(tuple, attnum, RelationGetDescr(rel), &isnull);
		nulls[n++] = false;
	}

	index_rescan(scan, NULL, 0, NULL, 0);
	tuple = index_getnext(scan, ForwardScanDirection);

	if (HeapTupleIsValid(tuple))
	{
		minmax[n] = heap_getattr(tuple, attnum, RelationGetDescr(rel), &isnull);
		nulls[n++] = false;
	}

	index_endscan(scan);

	return (nulls[0] || nulls[1]) ? MINMAX_NO_TUPLES : MINMAX_FOUND;
}