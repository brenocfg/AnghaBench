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
struct TYPE_3__ {int /*<<< orphan*/  parent_indexoid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ChunkIndexMapping ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_relation_index_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_index_constraint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_get_by_indexrelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static Oid
chunk_index_duplicate_index(Relation hypertable_rel, Chunk *src_chunk, Oid chunk_index_oid,
							Relation dest_chunk_rel, Oid index_tablespace)
{
	Relation chunk_index_rel = relation_open(chunk_index_oid, AccessShareLock);
	ChunkIndexMapping cim;
	Oid constraint_oid;
	Oid new_chunk_indexrelid;

	ts_chunk_index_get_by_indexrelid(src_chunk, chunk_index_oid, &cim);

	constraint_oid = get_index_constraint(cim.parent_indexoid);

	new_chunk_indexrelid = chunk_relation_index_create(hypertable_rel,
													   chunk_index_rel,
													   dest_chunk_rel,
													   OidIsValid(constraint_oid),
													   index_tablespace);

	relation_close(chunk_index_rel, NoLock);
	return new_chunk_indexrelid;
}