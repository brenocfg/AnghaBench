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
typedef  scalar_t__ int32 ;
struct TYPE_3__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/ * Name ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ChunkConstraints ;
typedef  int /*<<< orphan*/  ChunkConstraint ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_constraint_name ; 
 int /*<<< orphan*/  Anum_chunk_constraint_dimension_slice_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_hypertable_constraint_name ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_chunk_constraint ; 
 int /*<<< orphan*/ * chunk_constraints_add (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  namein ; 

__attribute__((used)) static ChunkConstraint *
chunk_constraints_add_from_tuple(ChunkConstraints *ccs, TupleInfo *ti)
{
	bool nulls[Natts_chunk_constraint];
	Datum values[Natts_chunk_constraint];
	int32 dimension_slice_id;
	Name constraint_name;
	Name hypertable_constraint_name;

	heap_deform_tuple(ti->tuple, ti->desc, values, nulls);

	constraint_name =
		DatumGetName(values[AttrNumberGetAttrOffset(Anum_chunk_constraint_constraint_name)]);

	if (nulls[AttrNumberGetAttrOffset(Anum_chunk_constraint_dimension_slice_id)])
	{
		dimension_slice_id = 0;
		hypertable_constraint_name = DatumGetName(
			values[AttrNumberGetAttrOffset(Anum_chunk_constraint_hypertable_constraint_name)]);
	}
	else
	{
		dimension_slice_id = DatumGetInt32(
			values[AttrNumberGetAttrOffset(Anum_chunk_constraint_dimension_slice_id)]);
		hypertable_constraint_name = DatumGetName(DirectFunctionCall1(namein, CStringGetDatum("")));
	}

	return chunk_constraints_add(ccs,
								 DatumGetInt32(values[AttrNumberGetAttrOffset(
									 Anum_chunk_constraint_chunk_id)]),
								 dimension_slice_id,
								 NameStr(*constraint_name),
								 NameStr(*hypertable_constraint_name));
}