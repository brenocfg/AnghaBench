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
struct TYPE_5__ {int /*<<< orphan*/  hypertable_constraint_name; int /*<<< orphan*/  constraint_name; int /*<<< orphan*/  dimension_slice_id; int /*<<< orphan*/  chunk_id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ ChunkConstraint ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_constraint_name ; 
 int /*<<< orphan*/  Anum_chunk_constraint_dimension_slice_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_hypertable_constraint_name ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_chunk_constraint ; 
 scalar_t__ is_dimension_constraint (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
chunk_constraint_fill_tuple_values(ChunkConstraint *cc, Datum values[Natts_chunk_constraint],
								   bool nulls[Natts_chunk_constraint])
{
	memset(values, 0, sizeof(Datum) * Natts_chunk_constraint);
	values[AttrNumberGetAttrOffset(Anum_chunk_constraint_chunk_id)] =
		Int32GetDatum(cc->fd.chunk_id);
	values[AttrNumberGetAttrOffset(Anum_chunk_constraint_dimension_slice_id)] =
		Int32GetDatum(cc->fd.dimension_slice_id);
	values[AttrNumberGetAttrOffset(Anum_chunk_constraint_constraint_name)] =
		NameGetDatum(&cc->fd.constraint_name);
	values[AttrNumberGetAttrOffset(Anum_chunk_constraint_hypertable_constraint_name)] =
		NameGetDatum(&cc->fd.hypertable_constraint_name);

	if (is_dimension_constraint(cc))
		nulls[AttrNumberGetAttrOffset(Anum_chunk_constraint_hypertable_constraint_name)] = true;
	else
		nulls[AttrNumberGetAttrOffset(Anum_chunk_constraint_dimension_slice_id)] = true;
}