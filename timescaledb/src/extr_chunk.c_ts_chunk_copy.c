#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * cube; int /*<<< orphan*/ * constraints; } ;
typedef  TYPE_1__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/ * ts_chunk_constraints_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_hypercube_copy (int /*<<< orphan*/ *) ; 

Chunk *
ts_chunk_copy(Chunk *chunk)
{
	Chunk *copy;

	copy = palloc(sizeof(Chunk));
	memcpy(copy, chunk, sizeof(Chunk));

	if (NULL != chunk->constraints)
		copy->constraints = ts_chunk_constraints_copy(chunk->constraints);

	if (NULL != chunk->cube)
		copy->cube = ts_hypercube_copy(chunk->cube);

	return copy;
}