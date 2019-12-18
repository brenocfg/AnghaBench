#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  id; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_6__ {TYPE_3__ fd; int /*<<< orphan*/  chunk_sizing_func; int /*<<< orphan*/  space; int /*<<< orphan*/  chunk_cache; int /*<<< orphan*/  main_table_relid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 TYPE_1__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_chunk_sizing_func_oid (TYPE_3__*) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_formdata_fill (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_guc_max_cached_chunks_per_hypertable ; 
 int /*<<< orphan*/  ts_subspace_store_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Hypertable *
hypertable_from_tuple(HeapTuple tuple, MemoryContext mctx, TupleDesc desc)
{
	Oid namespace_oid;
	Hypertable *h = MemoryContextAllocZero(mctx, sizeof(Hypertable));
	hypertable_formdata_fill(&h->fd, tuple, desc);

	namespace_oid = get_namespace_oid(NameStr(h->fd.schema_name), false);
	h->main_table_relid = get_relname_relid(NameStr(h->fd.table_name), namespace_oid);
	h->space = ts_dimension_scan(h->fd.id, h->main_table_relid, h->fd.num_dimensions, mctx);
	h->chunk_cache =
		ts_subspace_store_init(h->space, mctx, ts_guc_max_cached_chunks_per_hypertable);
	h->chunk_sizing_func = get_chunk_sizing_func_oid(&h->fd);

	return h;
}