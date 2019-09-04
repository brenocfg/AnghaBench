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
struct TYPE_5__ {void* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  next_copy_from; TYPE_1__ fromctx; int /*<<< orphan*/  dispatch; int /*<<< orphan*/ * estate; int /*<<< orphan*/  rel; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  CopyFromFunc ;
typedef  TYPE_2__ CopyChunkState ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateExecutorState () ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  ts_chunk_dispatch_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CopyChunkState *
copy_chunk_state_create(Hypertable *ht, Relation rel, CopyFromFunc from_func, void *fromctx)
{
	CopyChunkState *ccstate;
	EState *estate = CreateExecutorState();

	ccstate = palloc(sizeof(CopyChunkState));
	ccstate->rel = rel;
	ccstate->estate = estate;
	ccstate->dispatch = ts_chunk_dispatch_create(ht, estate);
	ccstate->fromctx.data = fromctx;
	ccstate->next_copy_from = from_func;

	return ccstate;
}