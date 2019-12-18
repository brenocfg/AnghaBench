#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  numelements; int /*<<< orphan*/  misses; int /*<<< orphan*/  hits; } ;
struct TYPE_13__ {void* (* create_entry ) (TYPE_3__*,TYPE_2__*) ;void* (* update_entry ) (TYPE_3__*,TYPE_2__*) ;TYPE_1__ stats; int /*<<< orphan*/  (* get_key ) (TYPE_2__*) ;int /*<<< orphan*/ * htab; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {void* result; } ;
typedef  int /*<<< orphan*/  HASHACTION ;
typedef  TYPE_2__ CacheQuery ;
typedef  TYPE_3__ Cache ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 void* stub2 (TYPE_3__*,TYPE_2__*) ; 
 void* stub3 (TYPE_3__*,TYPE_2__*) ; 

void *
ts_cache_fetch(Cache *cache, CacheQuery *query)
{
	bool found;
	HASHACTION action = cache->create_entry == NULL ? HASH_FIND : HASH_ENTER;

	if (cache->htab == NULL)
		elog(ERROR, "hash %s is not initialized", cache->name);

	query->result = hash_search(cache->htab, cache->get_key(query), action, &found);

	if (found)
	{
		cache->stats.hits++;

		if (cache->update_entry != NULL)
			query->result = cache->update_entry(cache, query);
	}
	else
	{
		cache->stats.misses++;

		if (cache->create_entry != NULL)
		{
			cache->stats.numelements++;
			query->result = cache->create_entry(cache, query);
		}
	}

	return query->result;
}