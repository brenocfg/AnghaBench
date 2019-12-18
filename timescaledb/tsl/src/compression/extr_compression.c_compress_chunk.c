#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Tuplesortstate ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_5__ {int natts; } ;
typedef  int /*<<< orphan*/  RowCompressor ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ColumnCompressionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  RelationClose (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * compress_chunk_populate_keys (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int*,int /*<<< orphan*/  const***) ; 
 int /*<<< orphan*/ * compress_chunk_sort_relation (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  reindex_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  row_compressor_append_sorted_rows (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  row_compressor_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  row_compressor_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  truncate_relation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_end (int /*<<< orphan*/ *) ; 

void
compress_chunk(Oid in_table, Oid out_table, const ColumnCompressionInfo **column_compression_info,
			   int num_compression_infos)
{
	int n_keys;
	const ColumnCompressionInfo **keys;

	/*We want to prevent other compressors from compressing this table,
	 * and we want to prevent INSERTs or UPDATEs which could mess up our compression.
	 * We may as well allow readers to keep reading the uncompressed data while
	 * we are compressing, so we only take an ExclusiveLock instead of AccessExclusive.
	 */
	Relation in_rel = relation_open(in_table, ExclusiveLock);
	/* we are _just_ INSERTing into the out_table so in principle we could take
	 * a RowExclusive lock, and let other operations read and write this table
	 * as we work. However, we currently compress each table as a oneshot, so
	 * we're taking the stricter lock to prevent accidents.
	 */
	Relation out_rel = relation_open(out_table, ExclusiveLock);
	// TODO error if out_rel is non-empty
	// TODO typecheck the output types
	int16 *in_column_offsets = compress_chunk_populate_keys(in_table,
															column_compression_info,
															num_compression_infos,
															&n_keys,
															&keys);

	TupleDesc in_desc = RelationGetDescr(in_rel);
	TupleDesc out_desc = RelationGetDescr(out_rel);

	Tuplesortstate *sorted_rel = compress_chunk_sort_relation(in_rel, n_keys, keys);

	RowCompressor row_compressor;

	Assert(num_compression_infos <= in_desc->natts);
	Assert(num_compression_infos <= out_desc->natts);

	row_compressor_init(&row_compressor,
						in_desc,
						out_rel,
						num_compression_infos,
						column_compression_info,
						in_column_offsets,
						out_desc->natts);

	row_compressor_append_sorted_rows(&row_compressor, sorted_rel, in_desc);

	row_compressor_finish(&row_compressor);

	tuplesort_end(sorted_rel);

	truncate_relation(in_table);

	/* recreate all indexes on out rel, we already have an exvclusive lock on it
	 * so the strong locks taken by reindex_relation shouldn't matter. */
	reindex_relation(out_table, 0, 0);

	RelationClose(out_rel);
	RelationClose(in_rel);
}