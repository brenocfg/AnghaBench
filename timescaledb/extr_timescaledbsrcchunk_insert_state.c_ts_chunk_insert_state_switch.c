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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  rel; int /*<<< orphan*/  result_relation_info; } ;
typedef  TYPE_1__ ChunkInsertState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecSetSlotDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ ResultRelInfo_OnConflictNotNull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ResultRelInfo_OnConflictProjInfoCompat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_projection_info_slot_compat (int /*<<< orphan*/ *) ; 

void
ts_chunk_insert_state_switch(ChunkInsertState *state)
{
	/*
	 * Adjust the slots descriptor.
	 *
	 * Note: we have to adjust the slot descriptor whether or not this chunk
	 * has a tup_conv_map since we reuse the same slot across chunks. thus the
	 * slot will be set to the last chunk's slot descriptor and NOT the
	 * hypertable's slot descriptor.
	 */
	if (ResultRelInfo_OnConflictNotNull(state->result_relation_info) &&
		ResultRelInfo_OnConflictProjInfoCompat(state->result_relation_info) != NULL)
	{
		TupleTableSlot *slot = get_projection_info_slot_compat(
			ResultRelInfo_OnConflictProjInfoCompat(state->result_relation_info));

		ExecSetSlotDescriptor(slot, RelationGetDescr(state->rel));
	}
}