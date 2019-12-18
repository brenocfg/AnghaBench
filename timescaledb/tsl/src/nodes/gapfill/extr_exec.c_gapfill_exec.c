#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {scalar_t__ state; scalar_t__ subslot_time; scalar_t__ gapfill_start; scalar_t__ next_timestamp; scalar_t__ gapfill_period; scalar_t__ gapfill_end; int /*<<< orphan*/  subslot; int /*<<< orphan*/  groups_initialized; scalar_t__ multigroup; } ;
typedef  TYPE_1__ GapFillState ;
typedef  int /*<<< orphan*/  CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FETCHED_LAST ; 
 scalar_t__ FETCHED_NEXT_GROUP ; 
 scalar_t__ FETCHED_NONE ; 
 scalar_t__ FETCHED_ONE ; 
 int /*<<< orphan*/ * gapfill_fetch_next_tuple (TYPE_1__*) ; 
 int /*<<< orphan*/ * gapfill_state_gaptuple_create (TYPE_1__*,scalar_t__) ; 
 scalar_t__ gapfill_state_is_new_group (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gapfill_state_reset_group (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gapfill_state_return_subplan_slot (TYPE_1__*) ; 
 int /*<<< orphan*/  gapfill_state_set_next (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
gapfill_exec(CustomScanState *node)
{
	GapFillState *state = (GapFillState *) node;
	TupleTableSlot *slot = NULL;

	while (true)
	{
		/* fetch next tuple from subplan */
		if (FETCHED_NONE == state->state)
		{
			slot = gapfill_fetch_next_tuple(state);
			if (slot)
			{
				if (state->multigroup && gapfill_state_is_new_group(state, slot))
					state->state = FETCHED_NEXT_GROUP;
				else
					state->state = FETCHED_ONE;

				gapfill_state_set_next(state, slot);
			}
			else
			{
				/*
				 * if GROUP BY has non time_bucket_gapfill columns but the
				 * query has not initialized the groups there is nothing we
				 * can do here
				 */
				if (state->multigroup && !state->groups_initialized)
					return NULL;
				else
					state->state = FETCHED_LAST;
			}
		}

		/* return any subplan tuples before gapfill_start */
		if (FETCHED_ONE == state->state && state->subslot_time < state->gapfill_start)
		{
			state->state = FETCHED_NONE;
			return gapfill_state_return_subplan_slot(state);
		}

		/* if we have tuple from subplan check if it needs to be inserted now */
		if (FETCHED_ONE == state->state && state->subslot_time == state->next_timestamp)
		{
			state->state = FETCHED_NONE;
			state->next_timestamp += state->gapfill_period;
			return gapfill_state_return_subplan_slot(state);
		}

		/* if we are within gapfill boundaries we need to insert tuple */
		if (state->next_timestamp < state->gapfill_end)
		{
			Assert(state->state != FETCHED_NONE);
			slot = gapfill_state_gaptuple_create(state, state->next_timestamp);
			state->next_timestamp += state->gapfill_period;
			return slot;
		}

		/* return any remaining subplan tuples after gapfill_end */
		if (FETCHED_ONE == state->state)
		{
			state->state = FETCHED_NONE;
			return gapfill_state_return_subplan_slot(state);
		}

		/*
		 * Done with current group, prepare for next
		 */
		if (FETCHED_NEXT_GROUP == state->state)
		{
			state->state = FETCHED_ONE;
			state->next_timestamp = state->gapfill_start;
			gapfill_state_reset_group(state, state->subslot);
			continue;
		}

		return NULL;
	}
}