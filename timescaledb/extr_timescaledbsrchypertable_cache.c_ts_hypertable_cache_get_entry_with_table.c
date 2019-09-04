#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hypertable; } ;
struct TYPE_4__ {char const* schema; char const* table; int /*<<< orphan*/  q; int /*<<< orphan*/  relid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ HypertableCacheQuery ;
typedef  TYPE_2__ HypertableCacheEntry ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 TYPE_2__* ts_cache_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Hypertable *
ts_hypertable_cache_get_entry_with_table(Cache *cache, Oid relid, const char *schema,
										 const char *table)
{
	HypertableCacheQuery query = {
		.relid = relid,
		.schema = schema,
		.table = table,
	};
	HypertableCacheEntry *entry = ts_cache_fetch(cache, &query.q);

	return entry->hypertable;
}