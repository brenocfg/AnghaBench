#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_11__ {int /*<<< orphan*/  type_oid; } ;
struct TYPE_10__ {scalar_t__ num_compressed_columns; void* decompressed_datums; void* decompressed_is_nulls; int /*<<< orphan*/  bistate; int /*<<< orphan*/  per_compressed_cols; int /*<<< orphan*/  mycid; int /*<<< orphan*/  out_rel; TYPE_1__* out_desc; } ;
struct TYPE_9__ {scalar_t__ natts; } ;
typedef  int /*<<< orphan*/  ScanKey ;
typedef  TYPE_2__ RowDecompressor ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CUSTOM_TYPE_COMPRESSED_DATA ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeBulkInsertState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetBulkInsertState () ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 int HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationClose (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_per_compressed_column (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* palloc (int) ; 
 int /*<<< orphan*/  populate_per_compressed_columns_from_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  reindex_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  row_decompressor_decompress_row (TYPE_2__*) ; 
 TYPE_3__* ts_custom_type_cache_get (int /*<<< orphan*/ ) ; 

void
decompress_chunk(Oid in_table, Oid out_table)
{
	/* these locks are taken in the order uncompressed table then compressed table
	 * for consistency with compress_chunk
	 */
	/* we are _just_ INSERTing into the out_table so in principle we could take
	 * a RowExclusive lock, and let other operations read and write this table
	 * as we work. However, we currently compress each table as a oneshot, so
	 * we're taking the stricter lock to prevent accidents.
	 */
	Relation out_rel = relation_open(out_table, ExclusiveLock);
	/*We want to prevent other decompressors from decompressing this table,
	 * and we want to prevent INSERTs or UPDATEs which could mess up our decompression.
	 * We may as well allow readers to keep reading the compressed data while
	 * we are compressing, so we only take an ExclusiveLock instead of AccessExclusive.
	 */
	Relation in_rel = relation_open(in_table, ExclusiveLock);
	// TODO error if out_rel is non-empty

	TupleDesc in_desc = RelationGetDescr(in_rel);
	TupleDesc out_desc = RelationGetDescr(out_rel);

	Oid compressed_data_type_oid = ts_custom_type_cache_get(CUSTOM_TYPE_COMPRESSED_DATA)->type_oid;

	Assert(in_desc->natts >= out_desc->natts);
	Assert(OidIsValid(compressed_data_type_oid));

	{
		RowDecompressor decompressor = {
			.per_compressed_cols = create_per_compressed_column(in_desc,
																out_desc,
																out_table,
																compressed_data_type_oid),
			.num_compressed_columns = in_desc->natts,

			.out_desc = out_desc,
			.out_rel = out_rel,

			.mycid = GetCurrentCommandId(true),
			.bistate = GetBulkInsertState(),

			/* cache memory used to store the decompressed datums/is_null for form_tuple */
			.decompressed_datums = palloc(sizeof(Datum) * out_desc->natts),
			.decompressed_is_nulls = palloc(sizeof(bool) * out_desc->natts),
		};
		Datum *compressed_datums = palloc(sizeof(*compressed_datums) * in_desc->natts);
		bool *compressed_is_nulls = palloc(sizeof(*compressed_is_nulls) * in_desc->natts);

		HeapTuple compressed_tuple;
		HeapScanDesc heapScan = heap_beginscan(in_rel, GetLatestSnapshot(), 0, (ScanKey) NULL);
		MemoryContext per_compressed_row_ctx =
			AllocSetContextCreate(CurrentMemoryContext,
								  "decompress chunk per-compressed row",
								  ALLOCSET_DEFAULT_SIZES);

		for (compressed_tuple = heap_getnext(heapScan, ForwardScanDirection);
			 compressed_tuple != NULL;
			 compressed_tuple = heap_getnext(heapScan, ForwardScanDirection))
		{
			MemoryContext old_ctx;

			Assert(HeapTupleIsValid(compressed_tuple));

			old_ctx = MemoryContextSwitchTo(per_compressed_row_ctx);

			heap_deform_tuple(compressed_tuple, in_desc, compressed_datums, compressed_is_nulls);
			populate_per_compressed_columns_from_data(decompressor.per_compressed_cols,
													  in_desc->natts,
													  compressed_datums,
													  compressed_is_nulls);

			row_decompressor_decompress_row(&decompressor);
			MemoryContextSwitchTo(old_ctx);
			MemoryContextReset(per_compressed_row_ctx);
		}

		heap_endscan(heapScan);
		FreeBulkInsertState(decompressor.bistate);
	}

	/* recreate all indexes on out rel, we already have an exvclusive lock on it
	 * so the strong locks taken by reindex_relation shouldn't matter. */
	reindex_relation(out_table, 0, 0);

	RelationClose(out_rel);
	RelationClose(in_rel);
}