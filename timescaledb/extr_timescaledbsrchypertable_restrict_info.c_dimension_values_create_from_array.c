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
struct TYPE_3__ {int /*<<< orphan*/  consttype; int /*<<< orphan*/  constvalue; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DimensionValues ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ Const ;
typedef  int /*<<< orphan*/  ArrayIterator ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  array_create_iterator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ array_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * dimension_values_create (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DimensionValues *
dimension_values_create_from_array(Const *c, bool user_or)
{
	ArrayIterator iterator = array_create_iterator(DatumGetArrayTypeP(c->constvalue), 0, NULL);
	Datum elem = (Datum) NULL;
	bool isnull;
	List *values = NIL;
	Oid base_el_type;

	while (array_iterate(iterator, &elem, &isnull))
	{
		if (!isnull)
			values = lappend(values, DatumGetPointer(elem));
	}

	/* it's an array type, lets get the base element type */
	base_el_type = get_element_type(c->consttype);
	if (base_el_type == InvalidOid)
		elog(ERROR, "Couldn't get base element type from array type: %d", c->consttype);

	return dimension_values_create(values, base_el_type, user_or);
}