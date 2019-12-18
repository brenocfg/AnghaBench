#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pstate; void* current; int /*<<< orphan*/  choose_next_subplan; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  pscan_len; } ;
struct TYPE_6__ {void* next_plan; } ;
typedef  int /*<<< orphan*/  ParallelContext ;
typedef  TYPE_1__ ParallelChunkAppendState ;
typedef  TYPE_2__ CustomScanState ;
typedef  TYPE_3__ ChunkAppendState ;

/* Variables and functions */
 void* INVALID_SUBPLAN_INDEX ; 
 int /*<<< orphan*/  choose_next_subplan_for_leader ; 
 int /*<<< orphan*/  chunk_append_get_lock_pointer () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_append_initialize_dsm(CustomScanState *node, ParallelContext *pcxt, void *coordinate)
{
	ChunkAppendState *state = (ChunkAppendState *) node;
	ParallelChunkAppendState *pstate = (ParallelChunkAppendState *) coordinate;

	memset(pstate, 0, node->pscan_len);

	state->lock = chunk_append_get_lock_pointer();
	pstate->next_plan = INVALID_SUBPLAN_INDEX;

	state->choose_next_subplan = choose_next_subplan_for_leader;
	state->current = INVALID_SUBPLAN_INDEX;
	state->pstate = pstate;
}