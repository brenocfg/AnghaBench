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
struct TYPE_5__ {int trans_value_isnull; int trans_value_initialized; } ;
struct TYPE_4__ {TYPE_2__* per_group_state; int /*<<< orphan*/ * per_query_state; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ FATransitionState ;
typedef  int /*<<< orphan*/  FAPerQueryState ;
typedef  TYPE_2__ FAPerGroupState ;
typedef  int /*<<< orphan*/  AggState ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static FATransitionState *
fa_transition_state_init(MemoryContext *fa_context, FAPerQueryState *qstate, AggState *fa_aggstate)
{
	FATransitionState *tstate = NULL;
	tstate = (FATransitionState *) MemoryContextAlloc(*fa_context, sizeof(*tstate));
	tstate->per_query_state = qstate;
	tstate->per_group_state =
		(FAPerGroupState *) MemoryContextAlloc(*fa_context, sizeof(*tstate->per_group_state));

	/* Need to init tstate->per_group_state->trans_value */
	tstate->per_group_state->trans_value_isnull = true;
	tstate->per_group_state->trans_value_initialized = false;
	return tstate;
}