#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_toc ;
struct TYPE_2__ {int /*<<< orphan*/ * pstate; int /*<<< orphan*/  current; int /*<<< orphan*/  choose_next_subplan; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  ParallelChunkAppendState ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_1__ ChunkAppendState ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SUBPLAN_INDEX ; 
 int /*<<< orphan*/  choose_next_subplan_for_worker ; 
 int /*<<< orphan*/  chunk_append_get_lock_pointer () ; 

__attribute__((used)) static void
chunk_append_initialize_worker(CustomScanState *node, shm_toc *toc, void *coordinate)
{
	ChunkAppendState *state = (ChunkAppendState *) node;
	ParallelChunkAppendState *pstate = (ParallelChunkAppendState *) coordinate;

	state->lock = chunk_append_get_lock_pointer();
	state->choose_next_subplan = choose_next_subplan_for_worker;
	state->current = INVALID_SUBPLAN_INDEX;
	state->pstate = pstate;
}