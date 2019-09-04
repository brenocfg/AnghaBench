#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  prev_cis_oid; int /*<<< orphan*/ * prev_cis; int /*<<< orphan*/  cache; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  arbiter_indexes; int /*<<< orphan*/  on_conflict; int /*<<< orphan*/ * hypertable_result_rel_info; TYPE_2__* estate; TYPE_1__* hypertable; } ;
struct TYPE_9__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_8__ {int /*<<< orphan*/  space; } ;
typedef  TYPE_1__ Hypertable ;
typedef  TYPE_2__ EState ;
typedef  TYPE_3__ ChunkDispatch ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ONCONFLICT_NONE ; 
 TYPE_3__* palloc0 (int) ; 
 int /*<<< orphan*/  ts_guc_max_open_chunks_per_insert ; 
 int /*<<< orphan*/  ts_subspace_store_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ChunkDispatch *
ts_chunk_dispatch_create(Hypertable *ht, EState *estate)
{
	ChunkDispatch *cd = palloc0(sizeof(ChunkDispatch));

	cd->hypertable = ht;
	cd->estate = estate;
	cd->hypertable_result_rel_info = NULL;
	cd->on_conflict = ONCONFLICT_NONE;
	cd->arbiter_indexes = NIL;
	cd->cmd_type = CMD_INSERT;
	cd->cache =
		ts_subspace_store_init(ht->space, estate->es_query_cxt, ts_guc_max_open_chunks_per_insert);
	cd->prev_cis = NULL;
	cd->prev_cis_oid = InvalidOid;

	return cd;
}