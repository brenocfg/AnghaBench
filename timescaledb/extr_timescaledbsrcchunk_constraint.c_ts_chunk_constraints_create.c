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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int num_constraints; int /*<<< orphan*/ * constraints; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ChunkConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_constraint_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_constraints_insert (TYPE_1__*) ; 

void
ts_chunk_constraints_create(ChunkConstraints *ccs, Oid chunk_oid, int32 chunk_id,
							Oid hypertable_oid, int32 hypertable_id)
{
	int i;

	chunk_constraints_insert(ccs);

	for (i = 0; i < ccs->num_constraints; i++)
		chunk_constraint_create(&ccs->constraints[i],
								chunk_oid,
								chunk_id,
								hypertable_oid,
								hypertable_id);
}