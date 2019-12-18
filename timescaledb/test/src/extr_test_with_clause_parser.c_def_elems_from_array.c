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
struct TYPE_3__ {int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  element_type; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  TYPE_1__ ArrayMetaState ;
typedef  int /*<<< orphan*/  ArrayIterator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  array_create_iterator (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 scalar_t__ array_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  def_elem_from_texts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
def_elems_from_array(ArrayType *with_clause_array)
{
	ArrayMetaState with_clause_meta = { .element_type = TEXTOID };
	ArrayIterator with_clause_iter;
	Datum with_clause_datum;
	bool with_clause_null;
	List *def_elems = NIL;

	get_typlenbyvalalign(with_clause_meta.element_type,
						 &with_clause_meta.typlen,
						 &with_clause_meta.typbyval,
						 &with_clause_meta.typalign);
	with_clause_iter = array_create_iterator(with_clause_array, 1, &with_clause_meta);

	while (array_iterate(with_clause_iter, &with_clause_datum, &with_clause_null))
	{
		Datum *with_clause_fields;
		int with_clause_elems;
		ArrayType *with_clause = DatumGetArrayTypeP(with_clause_datum);
		Assert(!with_clause_null);
		deconstruct_array(with_clause,
						  TEXTOID,
						  with_clause_meta.typlen,
						  with_clause_meta.typbyval,
						  with_clause_meta.typalign,
						  &with_clause_fields,
						  NULL,
						  &with_clause_elems);
		def_elems = lappend(def_elems, def_elem_from_texts(with_clause_fields, with_clause_elems));
	}
	return def_elems;
}