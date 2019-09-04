#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int /*<<< orphan*/ * slot; int /*<<< orphan*/ * tup_conv_map; TYPE_1__* result_relation_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  ri_RelationDesc; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ ChunkInsertState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecSetSlotDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecStoreTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_convert_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HeapTuple
ts_chunk_insert_state_convert_tuple(ChunkInsertState *state, HeapTuple tuple,
									TupleTableSlot **existing_slot)
{
	Relation chunkrel = state->result_relation_info->ri_RelationDesc;

	if (NULL == state->tup_conv_map)
		/* No conversion needed */
		return tuple;

	tuple = do_convert_tuple(tuple, state->tup_conv_map);

	ExecSetSlotDescriptor(state->slot, RelationGetDescr(chunkrel));
	ExecStoreTuple(tuple, state->slot, InvalidBuffer, true);

	if (NULL != existing_slot)
		*existing_slot = state->slot;

	return tuple;
}