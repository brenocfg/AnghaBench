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
struct TYPE_6__ {int /*<<< orphan*/  table_id; TYPE_1__* constraints; } ;
struct TYPE_5__ {int num_constraints; int /*<<< orphan*/ * constraints; } ;
typedef  int /*<<< orphan*/  ChunkScanCtx ;
typedef  int /*<<< orphan*/  ChunkResult ;
typedef  TYPE_1__ ChunkConstraints ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_PROCESSED ; 
 int /*<<< orphan*/  chunk_fill_stub (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ts_chunk_constraint_recreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChunkResult
chunk_recreate_constraint(ChunkScanCtx *ctx, Chunk *chunk)
{
	ChunkConstraints *ccs = chunk->constraints;
	int i;

	chunk_fill_stub(chunk, false);

	for (i = 0; i < ccs->num_constraints; i++)
		ts_chunk_constraint_recreate(&ccs->constraints[i], chunk->table_id);

	return CHUNK_PROCESSED;
}