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
struct TYPE_4__ {int /*<<< orphan*/  hypertable_id; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fd; int /*<<< orphan*/  hypertable_relid; int /*<<< orphan*/  table_id; int /*<<< orphan*/  constraints; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ChunkConstraint ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_constraint_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_constraint_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chunk_constraints_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 char* get_constraint_name (int /*<<< orphan*/ ) ; 

void
ts_chunk_constraint_create_on_chunk(Chunk *chunk, Oid constraint_oid)
{
	const char *constrname;
	ChunkConstraint *cc;

	constrname = get_constraint_name(constraint_oid);
	cc = chunk_constraints_add(chunk->constraints, chunk->fd.id, 0, NULL, constrname);

	chunk_constraint_insert(cc);

	chunk_constraint_create(cc,
							chunk->table_id,
							chunk->fd.id,
							chunk->hypertable_relid,
							chunk->fd.hypertable_id);
}