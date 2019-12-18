#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mctx; int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ TupleInfo ;
struct TYPE_7__ {int /*<<< orphan*/  column_name; int /*<<< orphan*/  interval_length; void* num_slices; int /*<<< orphan*/  integer_now_func; int /*<<< orphan*/  integer_now_func_schema; int /*<<< orphan*/  partitioning_func; int /*<<< orphan*/  partitioning_func_schema; int /*<<< orphan*/  column_type; int /*<<< orphan*/  aligned; void* hypertable_id; void* id; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ fd; int /*<<< orphan*/  column_attno; int /*<<< orphan*/  partitioning; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_dimension_aligned ; 
 int Anum_dimension_column_name ; 
 int Anum_dimension_column_type ; 
 int Anum_dimension_hypertable_id ; 
 int Anum_dimension_id ; 
 int Anum_dimension_integer_now_func ; 
 int Anum_dimension_integer_now_func_schema ; 
 int Anum_dimension_interval_length ; 
 int Anum_dimension_num_slices ; 
 int Anum_dimension_partitioning_func ; 
 int Anum_dimension_partitioning_func_schema ; 
 size_t AttrNumberGetAttrOffset (int) ; 
 scalar_t__ DIMENSION_TYPE_CLOSED ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 void* DatumGetInt16 (int /*<<< orphan*/ ) ; 
 void* DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_dimension ; 
 scalar_t__ dimension_type (TYPE_2__*) ; 
 int /*<<< orphan*/  get_attnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namecpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_partitioning_info_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dimension_fill_in_from_tuple(Dimension *d, TupleInfo *ti, Oid main_table_relid)
{
	Datum values[Natts_dimension];
	bool isnull[Natts_dimension];

	/*
	 * With need to use heap_deform_tuple() rather than GETSTRUCT(), since
	 * optional values may be omitted from the tuple.
	 */
	heap_deform_tuple(ti->tuple, ti->desc, values, isnull);

	d->type = dimension_type(ti);
	d->fd.id = DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_dimension_id)]);
	d->fd.hypertable_id =
		DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_dimension_hypertable_id)]);
	d->fd.aligned = DatumGetBool(values[AttrNumberGetAttrOffset(Anum_dimension_aligned)]);
	d->fd.column_type =
		DatumGetObjectId(values[AttrNumberGetAttrOffset(Anum_dimension_column_type)]);
	memcpy(&d->fd.column_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_dimension_column_name)]),
		   NAMEDATALEN);

	if (!isnull[Anum_dimension_partitioning_func_schema - 1] &&
		!isnull[Anum_dimension_partitioning_func - 1])
	{
		MemoryContext old;

		d->fd.num_slices =
			DatumGetInt16(values[AttrNumberGetAttrOffset(Anum_dimension_num_slices)]);

		memcpy(&d->fd.partitioning_func_schema,
			   DatumGetName(
				   values[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func_schema)]),
			   NAMEDATALEN);
		memcpy(&d->fd.partitioning_func,
			   DatumGetName(values[AttrNumberGetAttrOffset(Anum_dimension_partitioning_func)]),
			   NAMEDATALEN);

		old = MemoryContextSwitchTo(ti->mctx);
		d->partitioning = ts_partitioning_info_create(NameStr(d->fd.partitioning_func_schema),
													  NameStr(d->fd.partitioning_func),
													  NameStr(d->fd.column_name),
													  d->type,
													  main_table_relid);
		MemoryContextSwitchTo(old);
	}

	if (!isnull[Anum_dimension_integer_now_func_schema - 1] &&
		!isnull[Anum_dimension_integer_now_func - 1])
	{
		namecpy(&d->fd.integer_now_func_schema,
				DatumGetName(
					values[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func_schema)]));
		namecpy(&d->fd.integer_now_func,
				DatumGetName(values[AttrNumberGetAttrOffset(Anum_dimension_integer_now_func)]));
	}

	if (d->type == DIMENSION_TYPE_CLOSED)
		d->fd.num_slices = DatumGetInt16(values[Anum_dimension_num_slices - 1]);
	else
		d->fd.interval_length =
			DatumGetInt64(values[AttrNumberGetAttrOffset(Anum_dimension_interval_length)]);

	d->column_attno = get_attnum(main_table_relid, NameStr(d->fd.column_name));
}