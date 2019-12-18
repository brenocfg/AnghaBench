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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  compression_info_vec ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_6__ {scalar_t__ element_type; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_len; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_1__ HeapTupleData ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  TYPE_2__ ArrayMetaState ;
typedef  int /*<<< orphan*/  ArrayIterator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DatumGetHeapTupleHeaderCopy (int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_create_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ array_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  compression_info_vec_append (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * compression_info_vec_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_rowtype_tupdesc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static compression_info_vec *
compression_info_from_array(ArrayType *compression_info_arr, Oid form_oid)
{
	ArrayMetaState compression_info_arr_meta = {
		.element_type = form_oid,
	};
	ArrayIterator compression_info_iter;
	Datum compression_info_datum;
	bool is_null;
	compression_info_vec *compression_info = compression_info_vec_create(CurrentMemoryContext, 0);
	TupleDesc form_desc = NULL;

	get_typlenbyvalalign(compression_info_arr_meta.element_type,
						 &compression_info_arr_meta.typlen,
						 &compression_info_arr_meta.typbyval,
						 &compression_info_arr_meta.typalign);

	compression_info_iter =
		array_create_iterator(compression_info_arr, 0, &compression_info_arr_meta);

	while (array_iterate(compression_info_iter, &compression_info_datum, &is_null))
	{
		HeapTupleHeader form;
		HeapTupleData tmptup;

		Assert(!is_null);
		form = DatumGetHeapTupleHeaderCopy(compression_info_datum);
		Assert(HeapTupleHeaderGetTypeId(form) == form_oid);
		if (form_desc == NULL)
		{
			int32 formTypmod = HeapTupleHeaderGetTypMod(form);
			form_desc = lookup_rowtype_tupdesc(form_oid, formTypmod);
		}

		tmptup.t_len = HeapTupleHeaderGetDatumLength(form);
		tmptup.t_data = form;
		compression_info_vec_append(compression_info, (void *) GETSTRUCT(&tmptup));
	}
	if (form_desc != NULL)
		ReleaseTupleDesc(form_desc);
	return compression_info;
}