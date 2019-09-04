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
struct TYPE_5__ {int refcount; int release_on_commit; int /*<<< orphan*/  flags; int /*<<< orphan*/  hctl; int /*<<< orphan*/  numelements; int /*<<< orphan*/  name; int /*<<< orphan*/ * htab; } ;
typedef  TYPE_1__ Cache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextContains (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_memory_ctx (TYPE_1__*) ; 

void
ts_cache_init(Cache *cache)
{
	if (cache->htab != NULL)
	{
		elog(ERROR, "cache %s is already initialized", cache->name);
		return;
	}

	/*
	 * The cache object should have been created in its own context so that
	 * cache_destroy can just delete the context to free everything.
	 */
	Assert(MemoryContextContains(ts_cache_memory_ctx(cache), cache));

	cache->htab = hash_create(cache->name, cache->numelements, &cache->hctl, cache->flags);
	cache->refcount = 1;
	cache->release_on_commit = true;
}