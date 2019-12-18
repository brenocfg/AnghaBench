#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  cube; } ;
struct TYPE_16__ {scalar_t__ prev_cis_oid; TYPE_2__* prev_cis; int /*<<< orphan*/  cache; int /*<<< orphan*/  hypertable; } ;
struct TYPE_15__ {TYPE_1__* rel; } ;
struct TYPE_14__ {scalar_t__ rd_id; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_2__ ChunkInsertState ;
typedef  TYPE_3__ ChunkDispatch ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  destroy_chunk_insert_state ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ts_chunk_insert_state_create (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ts_chunk_insert_state_switch (TYPE_2__*) ; 
 TYPE_4__* ts_hypertable_get_or_create_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_subspace_store_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ts_subspace_store_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

extern ChunkInsertState *
ts_chunk_dispatch_get_chunk_insert_state(ChunkDispatch *dispatch, Point *point,
										 bool *cis_changed_out)
{
	ChunkInsertState *cis;

	Assert(cis_changed_out != NULL);
	cis = ts_subspace_store_get(dispatch->cache, point);
	*cis_changed_out = true;

	if (NULL == cis)
	{
		Chunk *new_chunk;

		new_chunk = ts_hypertable_get_or_create_chunk(dispatch->hypertable, point);

		if (NULL == new_chunk)
			elog(ERROR, "no chunk found or created");

		cis = ts_chunk_insert_state_create(new_chunk, dispatch);
		ts_subspace_store_add(dispatch->cache, new_chunk->cube, cis, destroy_chunk_insert_state);
	}
	else if (cis->rel->rd_id == dispatch->prev_cis_oid && cis == dispatch->prev_cis)
	{
		/* got the same item from cache as before */
		*cis_changed_out = false;
	}

	if (*cis_changed_out)
		ts_chunk_insert_state_switch(cis);

	Assert(cis != NULL);
	dispatch->prev_cis = cis;
	dispatch->prev_cis_oid = cis->rel->rd_id;
	return cis;
}