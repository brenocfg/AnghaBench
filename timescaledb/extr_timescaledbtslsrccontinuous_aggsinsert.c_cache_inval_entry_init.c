#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/ * partitioning; } ;
struct TYPE_7__ {int /*<<< orphan*/  greatest_modified_value; int /*<<< orphan*/  lowest_modified_value; int /*<<< orphan*/  previous_chunk_relid; TYPE_4__ hypertable_open_dimension; int /*<<< orphan*/  hypertable_relid; } ;
struct TYPE_6__ {int /*<<< orphan*/  space; int /*<<< orphan*/  main_table_relid; } ;
typedef  int /*<<< orphan*/  PartitioningInfo ;
typedef  TYPE_1__ Hypertable ;
typedef  TYPE_2__ ContinuousAggsCacheInvalEntry ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PG_INT64_MAX ; 
 int /*<<< orphan*/  PG_INT64_MIN ; 
 int /*<<< orphan*/  continuous_aggs_trigger_mctx ; 
 TYPE_4__* hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_1__* ts_hypertable_cache_get_entry_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 

__attribute__((used)) static inline void
cache_inval_entry_init(ContinuousAggsCacheInvalEntry *cache_entry, int32 hypertable_id)
{
	Cache *ht_cache = ts_hypertable_cache_pin();
	/* NOTE: we can remove the id=>relid scan, if it becomes an issue, by getting the
	 * hypertable_relid directly from the Chunk*/
	Hypertable *ht = ts_hypertable_cache_get_entry_by_id(ht_cache, hypertable_id);
	cache_entry->hypertable_relid = ht->main_table_relid;
	cache_entry->hypertable_open_dimension = *hyperspace_get_open_dimension(ht->space, 0);
	if (cache_entry->hypertable_open_dimension.partitioning != NULL)
	{
		PartitioningInfo *open_dim_part_info =
			MemoryContextAllocZero(continuous_aggs_trigger_mctx, sizeof(*open_dim_part_info));
		*open_dim_part_info = *cache_entry->hypertable_open_dimension.partitioning;
		cache_entry->hypertable_open_dimension.partitioning = open_dim_part_info;
	}
	cache_entry->previous_chunk_relid = InvalidOid;
	cache_entry->lowest_modified_value = PG_INT64_MAX;
	cache_entry->greatest_modified_value = PG_INT64_MIN;
	ts_cache_release(ht_cache);
}