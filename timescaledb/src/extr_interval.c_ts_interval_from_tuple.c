#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  integer_interval; int /*<<< orphan*/  time_interval; scalar_t__ is_time_interval; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_1__ HeapTupleData ;
typedef  TYPE_2__ FormData_ts_interval ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_integer_interval ; 
 int /*<<< orphan*/  Anum_is_time_interval ; 
 int /*<<< orphan*/  Anum_time_interval ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetHeapTupleHeader (scalar_t__) ; 
 int /*<<< orphan*/  DatumGetInt64 (scalar_t__) ; 
 int /*<<< orphan*/ * DatumGetIntervalP (scalar_t__) ; 
 int /*<<< orphan*/  DecrTupleDescRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int Natts_ts_interval ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc0 (int) ; 

FormData_ts_interval *
ts_interval_from_tuple(Datum interval)
{
	bool isnull[Natts_ts_interval];
	Datum values[Natts_ts_interval];
	HeapTupleHeader th;
	HeapTupleData tuple;
	FormData_ts_interval *invl;

	Oid rowType;
	int32 rowTypmod;
	TupleDesc rowdesc;

	th = DatumGetHeapTupleHeader(interval);
	rowType = HeapTupleHeaderGetTypeId(th);
	rowTypmod = HeapTupleHeaderGetTypMod(th);
	rowdesc = lookup_rowtype_tupdesc(rowType, rowTypmod);

	tuple.t_len = HeapTupleHeaderGetDatumLength(th);
	ItemPointerSetInvalid(&(tuple.t_self));
	tuple.t_tableOid = InvalidOid;
	tuple.t_data = th;

	heap_deform_tuple(&tuple, rowdesc, values, isnull);
	// lookup_rowtype_tupdesc gives a ref counted pointer
	DecrTupleDescRefCount(rowdesc);

	invl = palloc0(sizeof(FormData_ts_interval));

	Assert(!isnull[AttrNumberGetAttrOffset(Anum_is_time_interval)]);

	invl->is_time_interval = values[AttrNumberGetAttrOffset(Anum_is_time_interval)];
	if (invl->is_time_interval)
	{
		Assert(!isnull[AttrNumberGetAttrOffset(Anum_time_interval)]);
		Assert(isnull[AttrNumberGetAttrOffset(Anum_integer_interval)]);
		invl->time_interval =
			*DatumGetIntervalP(values[AttrNumberGetAttrOffset(Anum_time_interval)]);
	}
	else
	{
		Assert(isnull[AttrNumberGetAttrOffset(Anum_time_interval)]);
		Assert(!isnull[AttrNumberGetAttrOffset(Anum_integer_interval)]);
		invl->integer_interval =
			DatumGetInt64(values[AttrNumberGetAttrOffset(Anum_integer_interval)]);
	}

	return invl;
}