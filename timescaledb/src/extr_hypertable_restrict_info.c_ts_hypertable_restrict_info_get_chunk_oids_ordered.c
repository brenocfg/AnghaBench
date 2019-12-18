#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* cube; int /*<<< orphan*/  table_id; } ;
struct TYPE_11__ {TYPE_1__* space; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** slices; } ;
struct TYPE_9__ {scalar_t__ num_dimensions; int /*<<< orphan*/ * dimensions; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HypertableRestrictInfo ;
typedef  TYPE_3__ Hypertable ;
typedef  int /*<<< orphan*/  DimensionSlice ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int IS_OPEN_DIMENSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  chunk_cmp ; 
 int /*<<< orphan*/  chunk_cmp_reverse ; 
 TYPE_4__** hypertable_restrict_info_get_chunks (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_4__**,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_dimension_slice_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
ts_hypertable_restrict_info_get_chunk_oids_ordered(HypertableRestrictInfo *hri, Hypertable *ht,
												   LOCKMODE lockmode, List **nested_oids,
												   bool reverse)
{
	unsigned num_chunks;
	Chunk **chunks = hypertable_restrict_info_get_chunks(hri, ht, lockmode, &num_chunks);
	List *chunk_oids = NIL;
	List *slot_chunk_oids = NIL;
	DimensionSlice *slice = NULL;
	unsigned int i;

	if (num_chunks == 0)
		return NIL;

	Assert(ht->space->num_dimensions > 0);
	Assert(IS_OPEN_DIMENSION(&ht->space->dimensions[0]));

	if (reverse)
		qsort(chunks, num_chunks, sizeof(Chunk *), chunk_cmp_reverse);
	else
		qsort(chunks, num_chunks, sizeof(Chunk *), chunk_cmp);

	for (i = 0; i < num_chunks; i++)
	{
		Chunk *chunk = chunks[i];

		if (NULL != slice && ts_dimension_slice_cmp(slice, chunk->cube->slices[0]) != 0 &&
			slot_chunk_oids != NIL)
		{
			*nested_oids = lappend(*nested_oids, slot_chunk_oids);
			slot_chunk_oids = NIL;
		}

		if (NULL != nested_oids)
			slot_chunk_oids = lappend_oid(slot_chunk_oids, chunk->table_id);

		chunk_oids = lappend_oid(chunk_oids, chunk->table_id);
		slice = chunk->cube->slices[0];
	}

	if (slot_chunk_oids != NIL)
		*nested_oids = lappend(*nested_oids, slot_chunk_oids);

	return chunk_oids;
}