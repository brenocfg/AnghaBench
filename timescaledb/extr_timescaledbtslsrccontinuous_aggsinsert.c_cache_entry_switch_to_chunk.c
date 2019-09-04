#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  table_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_9__ {scalar_t__ previous_chunk_open_dimension; TYPE_2__ hypertable_open_dimension; int /*<<< orphan*/  previous_chunk_relid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ ContinuousAggsCacheInvalEntry ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ attno_find_by_attname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
cache_entry_switch_to_chunk(ContinuousAggsCacheInvalEntry *cache_entry, Oid chunk_id,
							Relation chunk_relation)
{
	Chunk *modified_tuple_chunk = ts_chunk_get_by_relid(chunk_id, 0, false);
	if (modified_tuple_chunk == NULL)
		elog(ERROR, "continuous agg trigger function must be called on hypertable chunks only");

	cache_entry->previous_chunk_relid = modified_tuple_chunk->table_id;
	cache_entry->previous_chunk_open_dimension =
		attno_find_by_attname(RelationGetDescr(chunk_relation),
							  &cache_entry->hypertable_open_dimension.fd.column_name);
	if (cache_entry->previous_chunk_open_dimension == InvalidAttrNumber)
		elog(ERROR, "continuous agg trigger function must be called on hypertable chunks only");
}