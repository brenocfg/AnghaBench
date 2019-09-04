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
typedef  scalar_t__ int16 ;
struct TYPE_3__ {scalar_t__ capacity; int /*<<< orphan*/  constraints; int /*<<< orphan*/  mctx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ChunkConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_CONSTRAINTS_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_constraints_expand(ChunkConstraints *ccs, int16 new_capacity)
{
	MemoryContext old;

	if (new_capacity <= ccs->capacity)
		return;

	old = MemoryContextSwitchTo(ccs->mctx);
	ccs->capacity = new_capacity;
	ccs->constraints = repalloc(ccs->constraints, CHUNK_CONSTRAINTS_SIZE(new_capacity));
	MemoryContextSwitchTo(old);
}