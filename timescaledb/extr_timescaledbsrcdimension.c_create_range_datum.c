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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_2__ DimensionSlice ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BlessTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static Datum
create_range_datum(FunctionCallInfo fcinfo, DimensionSlice *slice)
{
	TupleDesc tupdesc;
	Datum values[2];
	bool nulls[2] = { false };
	HeapTuple tuple;

	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "function returning record called in context that cannot accept type record");

	tupdesc = BlessTupleDesc(tupdesc);

	values[0] = Int64GetDatum(slice->fd.range_start);
	values[1] = Int64GetDatum(slice->fd.range_end);
	tuple = heap_form_tuple(tupdesc, values, nulls);

	return HeapTupleGetDatum(tuple);
}