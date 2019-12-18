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
struct TYPE_4__ {int /*<<< orphan*/  numelements; } ;
struct TYPE_5__ {TYPE_1__ stats; int /*<<< orphan*/  htab; } ;
typedef  TYPE_2__ Cache ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

bool
ts_cache_remove(Cache *cache, void *key)
{
	bool found;

	hash_search(cache->htab, key, HASH_REMOVE, &found);

	if (found)
		cache->stats.numelements--;

	return found;
}