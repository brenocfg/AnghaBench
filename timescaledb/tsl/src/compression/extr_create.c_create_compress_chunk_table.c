#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int id; int /*<<< orphan*/  hypertable_id; TYPE_1__ table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_21__ {int /*<<< orphan*/  table_id; TYPE_3__ fd; int /*<<< orphan*/  hypertable_relid; int /*<<< orphan*/  constraints; int /*<<< orphan*/  cube; } ;
struct TYPE_20__ {int /*<<< orphan*/  hypertable_id; int /*<<< orphan*/  num_dimensions; } ;
struct TYPE_17__ {int /*<<< orphan*/  associated_table_prefix; } ;
struct TYPE_19__ {TYPE_2__ fd; int /*<<< orphan*/  main_table_relid; TYPE_5__* space; } ;
typedef  TYPE_4__ Hypertable ;
typedef  TYPE_5__ Hyperspace ;
typedef  TYPE_6__ Chunk ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_rel_tablespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tablespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_table_next_seq_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_constraints_add_inheritable_constraints (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_constraints_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_constraints_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ts_chunk_create_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_create_table (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_create_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_insert_lock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_trigger_create_all_on_chunk (TYPE_4__*,TYPE_6__*) ; 

Chunk *
create_compress_chunk_table(Hypertable *compress_ht, Chunk *src_chunk)
{
	Hyperspace *hs = compress_ht->space;
	Catalog *catalog = ts_catalog_get();
	CatalogSecurityContext sec_ctx;
	Chunk *compress_chunk;

	/* Create a new chunk based on the hypercube */
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	compress_chunk =
		ts_chunk_create_stub(ts_catalog_table_next_seq_id(catalog, CHUNK), hs->num_dimensions);
	ts_catalog_restore_user(&sec_ctx);

	compress_chunk->fd.hypertable_id = hs->hypertable_id;
	compress_chunk->cube = src_chunk->cube;
	compress_chunk->hypertable_relid = compress_ht->main_table_relid;
	compress_chunk->constraints = ts_chunk_constraints_alloc(1, CurrentMemoryContext);
	namestrcpy(&compress_chunk->fd.schema_name, INTERNAL_SCHEMA_NAME);
	snprintf(compress_chunk->fd.table_name.data,
			 NAMEDATALEN,
			 "compress%s_%d_chunk",
			 NameStr(compress_ht->fd.associated_table_prefix),
			 compress_chunk->fd.id);

	;

	/* Insert chunk */
	ts_chunk_insert_lock(compress_chunk, RowExclusiveLock);

	/* only add inheritable constraints. no dimension constraints */
	ts_chunk_constraints_add_inheritable_constraints(compress_chunk->constraints,
													 compress_chunk->fd.id,
													 compress_chunk->hypertable_relid);

	/* Create the actual table relation for the chunk
	 * Note that we have to pick the tablespace here as the compressed ht doesn't have dimensions
	 * on which to base this decision. We simply pick the same tablespace as the uncompressed chunk
	 * for now.
	 */
	compress_chunk->table_id =
		ts_chunk_create_table(compress_chunk,
							  compress_ht,
							  get_tablespace_name(get_rel_tablespace(src_chunk->table_id)));

	if (!OidIsValid(compress_chunk->table_id))
		elog(ERROR, "could not create compress chunk table");

	/* Create the chunk's constraints*/
	ts_chunk_constraints_create(compress_chunk->constraints,
								compress_chunk->table_id,
								compress_chunk->fd.id,
								compress_chunk->hypertable_relid,
								compress_chunk->fd.hypertable_id);

	ts_trigger_create_all_on_chunk(compress_ht, compress_chunk);

	ts_chunk_index_create_all(compress_chunk->fd.hypertable_id,
							  compress_chunk->hypertable_relid,
							  compress_chunk->fd.id,
							  compress_chunk->table_id);

	return compress_chunk;
}