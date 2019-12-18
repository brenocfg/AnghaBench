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
struct TYPE_5__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_6__ {void* orderby_nullsfirst; void* orderby_asc; void* orderby_column_index; void* segmentby_column_index; void* algo_id; int /*<<< orphan*/  attname; int /*<<< orphan*/  hypertable_id; } ;
typedef  TYPE_2__ FormData_hypertable_compression ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_compression_algo_id ; 
 int /*<<< orphan*/  Anum_hypertable_compression_attname ; 
 int /*<<< orphan*/  Anum_hypertable_compression_hypertable_id ; 
 int /*<<< orphan*/  Anum_hypertable_compression_orderby_asc ; 
 int /*<<< orphan*/  Anum_hypertable_compression_orderby_column_index ; 
 int /*<<< orphan*/  Anum_hypertable_compression_orderby_nullsfirst ; 
 int /*<<< orphan*/  Anum_hypertable_compression_segmentby_column_index ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 void* BoolGetDatum (int /*<<< orphan*/ ) ; 
 void* DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int Natts_hypertable_compression ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hypertable_compression_fill_from_tuple(FormData_hypertable_compression *fd, TupleInfo *ti)
{
	Datum values[Natts_hypertable_compression];
	bool isnulls[Natts_hypertable_compression];

	heap_deform_tuple(ti->tuple, ti->desc, values, isnulls);

	Assert(!isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_hypertable_id)]);
	Assert(!isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_attname)]);
	Assert(!isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_algo_id)]);

	fd->hypertable_id =
		DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_hypertable_compression_hypertable_id)]);
	memcpy(&fd->attname,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_compression_attname)]),
		   NAMEDATALEN);
	fd->algo_id =
		DatumGetInt16(values[AttrNumberGetAttrOffset(Anum_hypertable_compression_algo_id)]);

	if (isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_segmentby_column_index)])
		fd->segmentby_column_index = 0;
	else
		fd->segmentby_column_index = DatumGetInt16(
			values[AttrNumberGetAttrOffset(Anum_hypertable_compression_segmentby_column_index)]);

	if (isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_column_index)])
		fd->orderby_column_index = 0;
	else
	{
		Assert(!isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_asc)]);
		Assert(!isnulls[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_nullsfirst)]);

		fd->orderby_column_index = DatumGetInt16(
			values[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_column_index)]);
		fd->orderby_asc =
			BoolGetDatum(values[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_asc)]);
		fd->orderby_nullsfirst = BoolGetDatum(
			values[AttrNumberGetAttrOffset(Anum_hypertable_compression_orderby_nullsfirst)]);
	}
}