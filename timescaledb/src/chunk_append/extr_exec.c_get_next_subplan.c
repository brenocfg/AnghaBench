#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_subplans; int /*<<< orphan*/  valid_subplans; int /*<<< orphan*/  runtime_initialized; scalar_t__ runtime_exclusion; } ;
typedef  TYPE_1__ ChunkAppendState ;

/* Variables and functions */
 int NO_MATCHING_SUBPLANS ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initialize_runtime_exclusion (TYPE_1__*) ; 

__attribute__((used)) static int
get_next_subplan(ChunkAppendState *state, int last_plan)
{
	if (last_plan == NO_MATCHING_SUBPLANS)
		return NO_MATCHING_SUBPLANS;

	if (state->runtime_exclusion)
	{
		if (!state->runtime_initialized)
			initialize_runtime_exclusion(state);

		/*
		 * bms_next_member will return -2 (NO_MATCHING_SUBPLANS) if there are
		 * no more members
		 */
		return bms_next_member(state->valid_subplans, last_plan);
	}
	else
	{
		int next_plan = last_plan + 1;

		if (next_plan >= state->num_subplans)
			return NO_MATCHING_SUBPLANS;

		return next_plan;
	}
}