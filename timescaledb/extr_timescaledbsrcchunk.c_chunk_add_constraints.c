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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  hypertable_relid; TYPE_1__ fd; int /*<<< orphan*/  constraints; int /*<<< orphan*/  cube; } ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int ts_chunk_constraints_add_dimension_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_chunk_constraints_add_inheritable_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chunk_add_constraints(Chunk *chunk)
{
	int num_added;

	num_added = ts_chunk_constraints_add_dimension_constraints(chunk->constraints,
															   chunk->fd.id,
															   chunk->cube);
	num_added += ts_chunk_constraints_add_inheritable_constraints(chunk->constraints,
																  chunk->fd.id,
																  chunk->hypertable_relid);

	return num_added;
}