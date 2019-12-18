#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_15__ {scalar_t__ typid; int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; } ;
struct TYPE_19__ {TYPE_2__ base; } ;
struct TYPE_18__ {int isnull; int /*<<< orphan*/  value; int /*<<< orphan*/  time; } ;
struct TYPE_17__ {size_t time_index; int /*<<< orphan*/  gapfill_typid; TYPE_1__** columns; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
struct TYPE_14__ {scalar_t__ typid; } ;
struct TYPE_13__ {scalar_t__ atttypid; } ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_3__ HeapTupleData ;
typedef  TYPE_4__ GapFillState ;
typedef  TYPE_5__ GapFillInterpolateSample ;
typedef  TYPE_6__ GapFillInterpolateColumnState ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DecrTupleDescRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int HeapTupleHeaderGetNatts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORDOID ; 
 TYPE_12__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  gapfill_datum_get_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gapfill_exec_expr (TYPE_4__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_3__*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gapfill_fetch_sample(GapFillState *state, GapFillInterpolateColumnState *column,
					 GapFillInterpolateSample *sample, Expr *lookup)
{
	HeapTupleHeader th;
	HeapTupleData tuple;
	TupleDesc tupdesc;
	Datum value;
	bool isnull;
	Datum datum = gapfill_exec_expr(state, lookup, &isnull);

	if (isnull)
	{
		sample->isnull = true;
		return;
	}

	th = DatumGetHeapTupleHeader(datum);
	if (HeapTupleHeaderGetNatts(th) != 2)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("interpolate RECORD arguments must have 2 elements")));

	/* Extract type information from the tuple itself */
	Assert(RECORDOID == HeapTupleHeaderGetTypeId(th));
	tupdesc = lookup_rowtype_tupdesc(HeapTupleHeaderGetTypeId(th), HeapTupleHeaderGetTypMod(th));

	/* Build a temporary HeapTuple control structure */
	tuple.t_len = HeapTupleHeaderGetDatumLength(th);
	ItemPointerSetInvalid(&(tuple.t_self));
	tuple.t_tableOid = InvalidOid;
	tuple.t_data = th;

	/* check first element in record matches timestamp datatype */
	if (TupleDescAttr(tupdesc, 0)->atttypid != state->columns[state->time_index]->typid)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("first argument of interpolate returned record must match used timestamp "
						"datatype")));

	/* check second element in record matches interpolate datatype */
	if (TupleDescAttr(tupdesc, 1)->atttypid != column->base.typid)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("second argument of interpolate returned record must match used "
						"interpolate datatype")));

	value = heap_getattr(&tuple, 1, tupdesc, &sample->isnull);
	if (!sample->isnull)
	{
		sample->time = gapfill_datum_get_internal(value, state->gapfill_typid);

		value = heap_getattr(&tuple, 2, tupdesc, &sample->isnull);
		if (!sample->isnull)
			sample->value = datumCopy(value, column->base.typbyval, column->base.typlen);
	}

	DecrTupleDescRefCount(tupdesc);
}