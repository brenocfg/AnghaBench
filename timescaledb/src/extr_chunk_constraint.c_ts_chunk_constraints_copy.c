#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  num_constraints; struct TYPE_8__* constraints; int /*<<< orphan*/  capacity; } ;
typedef  TYPE_1__ ChunkConstraints ;

/* Variables and functions */
 int CHUNK_CONSTRAINTS_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* palloc (int) ; 
 TYPE_1__* palloc0 (int) ; 

ChunkConstraints *
ts_chunk_constraints_copy(ChunkConstraints *ccs)
{
	ChunkConstraints *copy = palloc(sizeof(ChunkConstraints));

	memcpy(copy, ccs, sizeof(ChunkConstraints));
	copy->constraints = palloc0(CHUNK_CONSTRAINTS_SIZE(ccs->capacity));
	memcpy(copy->constraints, ccs->constraints, CHUNK_CONSTRAINTS_SIZE(ccs->num_constraints));

	return copy;
}