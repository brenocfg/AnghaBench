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
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ int16 ;
struct TYPE_5__ {int /*<<< orphan*/  compressed_chunk_id; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  constraints; TYPE_1__ fd; } ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  INVALID_CHUNK_ID ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  ts_chunk_constraints_alloc (scalar_t__,int /*<<< orphan*/ ) ; 

Chunk *
ts_chunk_create_stub(int32 id, int16 num_constraints)
{
	Chunk *chunk;

	chunk = palloc0(sizeof(Chunk));
	chunk->fd.id = id;
	chunk->fd.compressed_chunk_id = INVALID_CHUNK_ID;

	if (num_constraints > 0)
		chunk->constraints = ts_chunk_constraints_alloc(num_constraints, CurrentMemoryContext);

	return chunk;
}