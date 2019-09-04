#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cmp_proc_finfo; int /*<<< orphan*/  cmp_proc; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MinMaxResult ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FunctionCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  MINMAX_FOUND ; 
 int /*<<< orphan*/  MINMAX_NO_TUPLES ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int TYPECACHE_CMP_PROC ; 
 int TYPECACHE_CMP_PROC_FINFO ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static MinMaxResult
minmax_heapscan(Relation rel, Oid atttype, AttrNumber attnum, Datum minmax[2])
{
	HeapScanDesc scan;
	HeapTuple tuple;
	TypeCacheEntry *tce;
	bool nulls[2] = { true, true };

	/* Lookup the tuple comparison function from the type cache */
	tce = lookup_type_cache(atttype, TYPECACHE_CMP_PROC | TYPECACHE_CMP_PROC_FINFO);

	if (NULL == tce || !OidIsValid(tce->cmp_proc))
		elog(ERROR, "no comparison function for type %u", atttype);

	scan = heap_beginscan(rel, GetTransactionSnapshot(), 0, NULL);

	while ((tuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		bool isnull;
		Datum value = heap_getattr(tuple, attnum, RelationGetDescr(rel), &isnull);

		if (isnull)
			continue;

		/* Check for new min */
		if (nulls[0] || DatumGetInt32(FunctionCall2(&tce->cmp_proc_finfo, value, minmax[0])) < 0)
		{
			nulls[0] = false;
			minmax[0] = value;
		}

		/* Check for new max */
		if (nulls[1] || DatumGetInt32(FunctionCall2(&tce->cmp_proc_finfo, value, minmax[1])) > 0)
		{
			nulls[1] = false;
			minmax[1] = value;
		}
	}

	heap_endscan(scan);

	return (nulls[0] || nulls[1]) ? MINMAX_NO_TUPLES : MINMAX_FOUND;
}