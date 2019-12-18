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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {void* compressed_hypertable_id; int /*<<< orphan*/  compressed; int /*<<< orphan*/  chunk_target_size; int /*<<< orphan*/  chunk_sizing_func_name; int /*<<< orphan*/  chunk_sizing_func_schema; int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  associated_table_prefix; int /*<<< orphan*/  associated_schema_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; void* id; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ FormData_hypertable ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_associated_schema_name ; 
 int /*<<< orphan*/  Anum_hypertable_associated_table_prefix ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_sizing_func_name ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_sizing_func_schema ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_target_size ; 
 int /*<<< orphan*/  Anum_hypertable_compressed ; 
 int /*<<< orphan*/  Anum_hypertable_compressed_hypertable_id ; 
 int /*<<< orphan*/  Anum_hypertable_id ; 
 int /*<<< orphan*/  Anum_hypertable_num_dimensions ; 
 int /*<<< orphan*/  Anum_hypertable_schema_name ; 
 int /*<<< orphan*/  Anum_hypertable_table_name ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 void* DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetName (int /*<<< orphan*/ ) ; 
 void* INVALID_HYPERTABLE_ID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int Natts_hypertable ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hypertable_formdata_fill(FormData_hypertable *fd, const HeapTuple tuple, const TupleDesc desc)
{
	bool nulls[Natts_hypertable];
	Datum values[Natts_hypertable];

	heap_deform_tuple(tuple, desc, values, nulls);

	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_id)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_schema_name)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_table_name)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_associated_schema_name)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_associated_table_prefix)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_num_dimensions)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_schema)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_name)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_chunk_target_size)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_hypertable_compressed)]);

	fd->id = DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_hypertable_id)]);
	memcpy(&fd->schema_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_schema_name)]),
		   NAMEDATALEN);
	memcpy(&fd->table_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_table_name)]),
		   NAMEDATALEN);
	memcpy(&fd->associated_schema_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_associated_schema_name)]),
		   NAMEDATALEN);
	memcpy(&fd->associated_table_prefix,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_associated_table_prefix)]),
		   NAMEDATALEN);

	fd->num_dimensions =
		DatumGetInt16(values[AttrNumberGetAttrOffset(Anum_hypertable_num_dimensions)]);

	memcpy(&fd->chunk_sizing_func_schema,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_schema)]),
		   NAMEDATALEN);
	memcpy(&fd->chunk_sizing_func_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_name)]),
		   NAMEDATALEN);

	fd->chunk_target_size =
		DatumGetInt64(values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_target_size)]);
	fd->compressed = DatumGetBool(values[AttrNumberGetAttrOffset(Anum_hypertable_compressed)]);

	if (nulls[AttrNumberGetAttrOffset(Anum_hypertable_compressed_hypertable_id)])
		fd->compressed_hypertable_id = INVALID_HYPERTABLE_ID;
	else
		fd->compressed_hypertable_id = DatumGetInt32(
			values[AttrNumberGetAttrOffset(Anum_hypertable_compressed_hypertable_id)]);
}