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
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  ContinuousAggsCacheInvalEntry ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_INVALIDATION_THRESHOLD ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_inval_entry_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  continuous_aggs_cache_inval_htab ; 
 scalar_t__ hash_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

__attribute__((used)) static void
cache_inval_htab_write(void)
{
	HASH_SEQ_STATUS hash_seq;
	ContinuousAggsCacheInvalEntry *current_entry;
	Catalog *catalog;

	if (hash_get_num_entries(continuous_aggs_cache_inval_htab) == 0)
		return;

	catalog = ts_catalog_get();

	/* The invalidation threshold must remain locked until the end of
	 * the transaction to ensure the materializer will see our updates,
	 * so we explicitly lock it here
	 */
	LockRelationOid(catalog_get_table_id(catalog, CONTINUOUS_AGGS_INVALIDATION_THRESHOLD),
					AccessShareLock);

	hash_seq_init(&hash_seq, continuous_aggs_cache_inval_htab);
	while ((current_entry = hash_seq_search(&hash_seq)) != NULL)
		cache_inval_entry_write(current_entry);
}