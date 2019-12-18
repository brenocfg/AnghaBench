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
struct TYPE_3__ {void* compressed_chunk_id; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; void* hypertable_id; void* id; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ FormData_chunk ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_compressed_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_hypertable_id ; 
 int /*<<< orphan*/  Anum_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_schema_name ; 
 int /*<<< orphan*/  Anum_chunk_table_name ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 void* DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetName (int /*<<< orphan*/ ) ; 
 void* INVALID_CHUNK_ID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int Natts_chunk ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_formdata_fill(FormData_chunk *fd, const HeapTuple tuple, const TupleDesc desc)
{
	bool nulls[Natts_chunk];
	Datum values[Natts_chunk];

	heap_deform_tuple(tuple, desc, values, nulls);

	Assert(!nulls[AttrNumberGetAttrOffset(Anum_chunk_id)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_chunk_hypertable_id)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_chunk_schema_name)]);
	Assert(!nulls[AttrNumberGetAttrOffset(Anum_chunk_table_name)]);

	fd->id = DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_chunk_id)]);
	fd->hypertable_id = DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_chunk_hypertable_id)]);
	memcpy(&fd->schema_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_chunk_schema_name)]),
		   NAMEDATALEN);
	memcpy(&fd->table_name,
		   DatumGetName(values[AttrNumberGetAttrOffset(Anum_chunk_table_name)]),
		   NAMEDATALEN);

	if (nulls[AttrNumberGetAttrOffset(Anum_chunk_compressed_chunk_id)])
		fd->compressed_chunk_id = INVALID_CHUNK_ID;
	else
		fd->compressed_chunk_id =
			DatumGetInt32(values[AttrNumberGetAttrOffset(Anum_chunk_compressed_chunk_id)]);
}