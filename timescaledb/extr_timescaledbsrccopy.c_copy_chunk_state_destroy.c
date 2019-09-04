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
struct TYPE_3__ {int /*<<< orphan*/  estate; int /*<<< orphan*/  dispatch; } ;
typedef  TYPE_1__ CopyChunkState ;

/* Variables and functions */
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_dispatch_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_chunk_state_destroy(CopyChunkState *ccstate)
{
	ts_chunk_dispatch_destroy(ccstate->dispatch);
	FreeExecutorState(ccstate->estate);
}