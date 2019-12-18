#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int id; int /*<<< orphan*/  hypertable_id; TYPE_1__ table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_28__ {int /*<<< orphan*/  table_id; TYPE_2__ fd; int /*<<< orphan*/  hypertable_relid; int /*<<< orphan*/  constraints; TYPE_5__* cube; } ;
struct TYPE_27__ {int /*<<< orphan*/  num_slices; int /*<<< orphan*/  slices; } ;
struct TYPE_26__ {int /*<<< orphan*/  hypertable_id; int /*<<< orphan*/  num_dimensions; } ;
struct TYPE_25__ {int /*<<< orphan*/  main_table_relid; TYPE_4__* space; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ Hyperspace ;
typedef  TYPE_5__ Hypercube ;
typedef  TYPE_6__ Chunk ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  calculate_and_set_new_chunk_interval (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunk_collision_resolve (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_table_next_seq_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_add_constraints (TYPE_6__*) ; 
 int /*<<< orphan*/  ts_chunk_constraints_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ts_chunk_create_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_create_table (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_create_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_insert_lock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_slice_insert_multi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ts_hypercube_calculate_from_point (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_hypertable_select_tablespace_name (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ts_trigger_create_all_on_chunk (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static Chunk *
chunk_create_after_lock(Hypertable *ht, Point *p, const char *schema, const char *prefix)
{
	Hyperspace *hs = ht->space;
	Catalog *catalog = ts_catalog_get();
	CatalogSecurityContext sec_ctx;
	Hypercube *cube;
	Chunk *chunk;

	/*
	 * If the user has enabled adaptive chunking, call the function to
	 * calculate and set the new chunk time interval.
	 */
	calculate_and_set_new_chunk_interval(ht, p);

	/* Calculate the hypercube for a new chunk that covers the tuple's point */
	cube = ts_hypercube_calculate_from_point(hs, p);

	/* Resolve collisions with other chunks by cutting the new hypercube */
	chunk_collision_resolve(hs, cube, p);

	/* Create a new chunk based on the hypercube */
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	chunk = ts_chunk_create_stub(ts_catalog_table_next_seq_id(catalog, CHUNK), hs->num_dimensions);
	ts_catalog_restore_user(&sec_ctx);

	chunk->fd.hypertable_id = hs->hypertable_id;
	chunk->cube = cube;
	chunk->hypertable_relid = ht->main_table_relid;
	namestrcpy(&chunk->fd.schema_name, schema);
	snprintf(chunk->fd.table_name.data, NAMEDATALEN, "%s_%d_chunk", prefix, chunk->fd.id);

	/* Insert chunk */
	ts_chunk_insert_lock(chunk, RowExclusiveLock);

	/* Insert any new dimension slices */
	ts_dimension_slice_insert_multi(cube->slices, cube->num_slices);

	/* Add metadata for dimensional and inheritable constraints */
	ts_chunk_add_constraints(chunk);

	/* Create the actual table relation for the chunk */
	chunk->table_id =
		ts_chunk_create_table(chunk, ht, ts_hypertable_select_tablespace_name(ht, chunk));

	if (!OidIsValid(chunk->table_id))
		elog(ERROR, "could not create chunk table");

	/* Create the chunk's constraints, triggers, and indexes */
	ts_chunk_constraints_create(chunk->constraints,
								chunk->table_id,
								chunk->fd.id,
								chunk->hypertable_relid,
								chunk->fd.hypertable_id);

	ts_trigger_create_all_on_chunk(ht, chunk);

	ts_chunk_index_create_all(chunk->fd.hypertable_id,
							  chunk->hypertable_relid,
							  chunk->fd.id,
							  chunk->table_id);

	return chunk;
}