#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_7__ {int /*<<< orphan*/  table_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_constraint_name ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_constraint_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relation_constraint_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ts_chunk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_index_delete (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
chunk_constraint_delete_metadata(TupleInfo *ti)
{
	bool isnull;
	Datum constrname =
		heap_getattr(ti->tuple, Anum_chunk_constraint_constraint_name, ti->desc, &isnull);
	int32 chunk_id =
		DatumGetInt32(heap_getattr(ti->tuple, Anum_chunk_constraint_chunk_id, ti->desc, &isnull));
	Chunk *chunk = ts_chunk_get_by_id(chunk_id, 0, true);
	Oid index_relid = get_constraint_index(
		get_relation_constraint_oid(chunk->table_id, NameStr(*DatumGetName(constrname)), true));

	/*
	 * If this is an index constraint, we need to cleanup the index
	 * metadata. Don't drop the index though, since that will happend when
	 * the constraint is dropped.
	 */
	if (OidIsValid(index_relid))
		ts_chunk_index_delete(chunk, index_relid, false);

	ts_catalog_delete(ti->scanrel, ti->tuple);
}