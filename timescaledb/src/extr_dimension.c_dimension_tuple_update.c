#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_2__ TupleInfo ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_6__ {scalar_t__ num_slices; scalar_t__ interval_length; int /*<<< orphan*/  integer_now_func_schema; int /*<<< orphan*/  integer_now_func; int /*<<< orphan*/  partitioning_func_schema; int /*<<< orphan*/  partitioning_func; int /*<<< orphan*/  column_type; int /*<<< orphan*/  column_name; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_dimension_column_name ; 
 int /*<<< orphan*/  Anum_dimension_column_type ; 
 int /*<<< orphan*/  Anum_dimension_integer_now_func ; 
 int /*<<< orphan*/  Anum_dimension_integer_now_func_schema ; 
 int /*<<< orphan*/  Anum_dimension_interval_length ; 
 int /*<<< orphan*/  Anum_dimension_num_slices ; 
 int /*<<< orphan*/  Anum_dimension_partitioning_func ; 
 int /*<<< orphan*/  Anum_dimension_partitioning_func_schema ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  Int64GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int Natts_dimension ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_update_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
dimension_tuple_update(TupleInfo *ti, void *data)
{
	Dimension *dim = data;
	HeapTuple tuple;
	Datum values[Natts_dimension];
	bool nulls[Natts_dimension];
	CatalogSecurityContext sec_ctx;

	heap_deform_tuple(ti->tuple, ti->desc, values, nulls);

	Assert((dim->fd.num_slices <= 0 && dim->fd.interval_length > 0) ||
		   (dim->fd.num_slices > 0 && dim->fd.interval_length <= 0));

	values[AttrNumberGetAttrOffset(Anum_dimension_column_name)] =
		NameGetDatum(&dim->fd.column_name);
	values[AttrNumberGetAttrOffset(Anum_dimension_column_type)] =
		ObjectIdGetDatum(dim->fd.column_type);
	values[AttrNumberGetAttrOffset(Anum_dimension_num_slices)] = Int16GetDatum(dim->fd.num_slices);

	if (!nulls[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func)] &&
		!nulls[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func_schema)])
	{
		values[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func)] =
			NameGetDatum(&dim->fd.partitioning_func);
		values[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func_schema)] =
			NameGetDatum(&dim->fd.partitioning_func_schema);
	}

	if (*NameStr(dim->fd.integer_now_func) != '\0' &&
		*NameStr(dim->fd.integer_now_func_schema) != '\0')
	{
		values[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func)] =
			NameGetDatum(&dim->fd.integer_now_func);
		values[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func_schema)] =
			NameGetDatum(&dim->fd.integer_now_func_schema);
		nulls[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func)] = false;
		nulls[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func_schema)] = false;
	}

	if (!nulls[AttrNumberGetAttrOffset(Anum_dimension_interval_length)])
		values[AttrNumberGetAttrOffset(Anum_dimension_interval_length)] =
			Int64GetDatum(dim->fd.interval_length);

	tuple = heap_form_tuple(ti->desc, values, nulls);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_update_tid(ti->scanrel, &ti->tuple->t_self, tuple);
	ts_catalog_restore_user(&sec_ctx);

	return SCAN_DONE;
}