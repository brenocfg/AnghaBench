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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ fd; int /*<<< orphan*/ * partitioning; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  ERRCODE_NOT_NULL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (TYPE_2__*) ; 
 int /*<<< orphan*/  ts_partitioning_func_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_time_value_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
tuple_get_time(Dimension *d, HeapTuple tuple, AttrNumber col, TupleDesc tupdesc)
{
	Datum datum;
	bool isnull;
	Oid dimtype;

	datum = heap_getattr(tuple, col, tupdesc, &isnull);

	if (NULL != d->partitioning)
		datum = ts_partitioning_func_apply(d->partitioning, datum);

	Assert(d->type == DIMENSION_TYPE_OPEN);

	dimtype = ts_dimension_get_partition_type(d);

	if (isnull)
		ereport(ERROR,
				(errcode(ERRCODE_NOT_NULL_VIOLATION),
				 errmsg("NULL value in column \"%s\" violates not-null constraint",
						NameStr(d->fd.column_name)),
				 errhint("Columns used for time partitioning cannot be NULL")));

	return ts_time_value_to_internal(datum, dimtype);
}