#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  IndexInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_create_post_adjustment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void
ts_chunk_index_create_from_adjusted_index_info(int32 hypertable_id, Relation hypertable_idxrel,
											   int32 chunk_id, Relation chunkrel,
											   IndexInfo *indexinfo)
{
	Oid chunk_indexrelid = ts_chunk_index_create_post_adjustment(hypertable_id,
																 hypertable_idxrel,
																 chunkrel,
																 indexinfo,
																 false,
																 false);

	chunk_index_insert(chunk_id,
					   get_rel_name(chunk_indexrelid),
					   hypertable_id,
					   get_rel_name(RelationGetRelid(hypertable_idxrel)));
}