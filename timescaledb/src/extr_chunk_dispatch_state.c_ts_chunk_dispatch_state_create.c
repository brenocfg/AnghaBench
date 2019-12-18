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
struct TYPE_4__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_5__ {TYPE_1__ cscan_state; int /*<<< orphan*/ * subplan; int /*<<< orphan*/  hypertable_relid; } ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ChunkDispatchState ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomScanState ; 
 int /*<<< orphan*/  chunk_dispatch_state_methods ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 

ChunkDispatchState *
ts_chunk_dispatch_state_create(Oid hypertable_relid, Plan *subplan)
{
	ChunkDispatchState *state;

	state = (ChunkDispatchState *) newNode(sizeof(ChunkDispatchState), T_CustomScanState);
	state->hypertable_relid = hypertable_relid;
	state->subplan = subplan;
	state->cscan_state.methods = &chunk_dispatch_state_methods;
	return state;
}