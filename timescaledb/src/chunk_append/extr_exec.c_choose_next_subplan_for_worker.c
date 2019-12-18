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
struct TYPE_6__ {size_t current; int num_subplans; int filtered_first_partial_plan; int /*<<< orphan*/  lock; TYPE_1__* pstate; } ;
struct TYPE_5__ {int* finished; int next_plan; } ;
typedef  TYPE_1__ ParallelChunkAppendState ;
typedef  TYPE_2__ ChunkAppendState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INVALID_SUBPLAN_INDEX ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int NO_MATCHING_SUBPLANS ; 
 void* get_next_subplan (TYPE_2__*,int) ; 

__attribute__((used)) static void
choose_next_subplan_for_worker(ChunkAppendState *state)
{
	ParallelChunkAppendState *pstate = state->pstate;
	int next_plan;
	int start;

	LWLockAcquire(state->lock, LW_EXCLUSIVE);

	/* mark just completed subplan as finished */
	if (state->current >= 0)
		pstate->finished[state->current] = true;

	if (pstate->next_plan == INVALID_SUBPLAN_INDEX)
		next_plan = get_next_subplan(state, INVALID_SUBPLAN_INDEX);
	else
		next_plan = pstate->next_plan;

	if (next_plan == NO_MATCHING_SUBPLANS)
	{
		/* all subplans are finished */
		pstate->next_plan = NO_MATCHING_SUBPLANS;
		state->current = NO_MATCHING_SUBPLANS;
		LWLockRelease(state->lock);
		return;
	}

	start = next_plan;

	/* skip finished subplans */
	while (pstate->finished[next_plan])
	{
		next_plan = get_next_subplan(state, next_plan);

		/* wrap around if we reach end of subplan list */
		if (next_plan < 0)
			next_plan = get_next_subplan(state, INVALID_SUBPLAN_INDEX);

		if (next_plan == start || next_plan < 0)
		{
			/*
			 * back at start of search so all subplans are finished
			 *
			 * next_plan should not be < 0 because this means there
			 * are no valid subplans and then the function would
			 * have returned at the check before the while loop but
			 * static analysis marked this so might as well include
			 * that in the check
			 */
			Assert(next_plan >= 0);
			pstate->next_plan = NO_MATCHING_SUBPLANS;
			state->current = NO_MATCHING_SUBPLANS;
			LWLockRelease(state->lock);
			return;
		}
	}

	Assert(next_plan >= 0 && next_plan < state->num_subplans);
	state->current = next_plan;

	/*
	 * if this is not a partial plan we mark it as finished
	 * immediately so it does not get assigned another worker
	 */
	if (next_plan < state->filtered_first_partial_plan)
		pstate->finished[next_plan] = true;

	/* advance next_plan for next worker */
	pstate->next_plan = get_next_subplan(state, state->current);
	/*
	 * if we reach the end of the list of subplans we set next_plan
	 * to INVALID_SUBPLAN_INDEX to allow rechecking unfinished subplans
	 * on next call
	 */
	if (pstate->next_plan < 0)
		pstate->next_plan = INVALID_SUBPLAN_INDEX;

	LWLockRelease(state->lock);
}