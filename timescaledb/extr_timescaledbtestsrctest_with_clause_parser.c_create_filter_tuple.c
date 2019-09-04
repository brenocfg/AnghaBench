#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/ * defname; int /*<<< orphan*/ * defnamespace; } ;
struct TYPE_7__ {int natts; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ DefElem ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  CStringGetTextDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * defGetString (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_form_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 void* palloc0 (int) ; 

__attribute__((used)) static HeapTuple
create_filter_tuple(TupleDesc tuple_desc, DefElem *d, bool within)
{
	Datum *values = palloc0(sizeof(*values) * tuple_desc->natts);
	bool *nulls = palloc0(sizeof(*nulls) * tuple_desc->natts);

	Assert(tuple_desc->natts >= 4);

	if (d->defnamespace != NULL)
		values[0] = CStringGetTextDatum(d->defnamespace);
	else
		nulls[0] = true;

	if (d->defname != NULL)
		values[1] = CStringGetTextDatum(d->defname);
	else
		nulls[1] = true;

	if (d->arg != NULL)
		values[2] = CStringGetTextDatum(defGetString(d));
	else
		nulls[2] = true;

	values[3] = BoolGetDatum(within);
	return heap_form_tuple(tuple_desc, values, nulls);
}