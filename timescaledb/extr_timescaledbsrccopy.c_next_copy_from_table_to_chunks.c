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
struct TYPE_4__ {int /*<<< orphan*/  scandesc; } ;
struct TYPE_5__ {int /*<<< orphan*/  rel; TYPE_1__ fromctx; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ CopyChunkState ;

/* Variables and functions */
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
next_copy_from_table_to_chunks(CopyChunkState *ccstate, ExprContext *econtext, Datum *values,
							   bool *nulls, Oid *tuple_oid)
{
	HeapScanDesc scandesc = ccstate->fromctx.scandesc;
	HeapTuple tuple = heap_getnext(scandesc, ForwardScanDirection);

	if (!HeapTupleIsValid(tuple))
		return false;

	heap_deform_tuple(tuple, RelationGetDescr(ccstate->rel), values, nulls);
	*tuple_oid = HeapTupleGetOid(tuple);

	return true;
}