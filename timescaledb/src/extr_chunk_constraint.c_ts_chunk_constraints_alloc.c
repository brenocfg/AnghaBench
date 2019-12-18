#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ capacity; int /*<<< orphan*/  constraints; scalar_t__ num_dimension_constraints; scalar_t__ num_constraints; int /*<<< orphan*/  mctx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ChunkConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_CONSTRAINTS_SIZE (scalar_t__) ; 
 scalar_t__ DEFAULT_EXTRA_CONSTRAINTS_SIZE ; 
 TYPE_1__* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextAllocZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ChunkConstraints *
ts_chunk_constraints_alloc(int size_hint, MemoryContext mctx)
{
	ChunkConstraints *ccs = MemoryContextAlloc(mctx, sizeof(ChunkConstraints));

	ccs->mctx = mctx;
	ccs->capacity = size_hint + DEFAULT_EXTRA_CONSTRAINTS_SIZE;
	ccs->num_constraints = 0;
	ccs->num_dimension_constraints = 0;
	ccs->constraints = MemoryContextAllocZero(mctx, CHUNK_CONSTRAINTS_SIZE(ccs->capacity));

	return ccs;
}