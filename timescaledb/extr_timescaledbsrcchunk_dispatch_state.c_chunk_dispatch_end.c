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
struct TYPE_5__ {int /*<<< orphan*/  hypertable_cache; int /*<<< orphan*/  dispatch; } ;
struct TYPE_4__ {int /*<<< orphan*/  custom_ps; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_1__ CustomScanState ;
typedef  TYPE_2__ ChunkDispatchState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_dispatch_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_dispatch_end(CustomScanState *node)
{
	ChunkDispatchState *state = (ChunkDispatchState *) node;
	PlanState *substate = linitial(node->custom_ps);

	ExecEndNode(substate);
	ts_chunk_dispatch_destroy(state->dispatch);
	ts_cache_release(state->hypertable_cache);
}