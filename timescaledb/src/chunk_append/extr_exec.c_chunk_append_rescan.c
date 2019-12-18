#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num_subplans; int runtime_initialized; int /*<<< orphan*/ * valid_subplans; int /*<<< orphan*/  params; scalar_t__ runtime_exclusion; int /*<<< orphan*/  current; int /*<<< orphan*/ * subplanstates; } ;
struct TYPE_6__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;
struct TYPE_8__ {TYPE_2__ ss; } ;
typedef  TYPE_3__ CustomScanState ;
typedef  TYPE_4__ ChunkAppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_SUBPLAN_INDEX ; 
 int /*<<< orphan*/  UpdateChangedParamSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_append_rescan(CustomScanState *node)
{
	ChunkAppendState *state = (ChunkAppendState *) node;
	int i;

	for (i = 0; i < state->num_subplans; i++)
	{
		if (node->ss.ps.chgParam != NULL)
			UpdateChangedParamSet(state->subplanstates[i], node->ss.ps.chgParam);

		ExecReScan(state->subplanstates[i]);
	}
	state->current = INVALID_SUBPLAN_INDEX;

	/*
	 * detect changed params and reset runtime exclusion state
	 */
	if (state->runtime_exclusion && bms_overlap(node->ss.ps.chgParam, state->params))
	{
		bms_free(state->valid_subplans);
		state->valid_subplans = NULL;
		state->runtime_initialized = false;
	}
}