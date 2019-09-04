#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  size_t uint16 ;
struct TYPE_6__ {size_t* bmpcache_mru; int* bmpcache_lru; TYPE_1__** bmpcache; int /*<<< orphan*/ * bmpcache_count; } ;
struct TYPE_7__ {TYPE_2__ cache; } ;
struct TYPE_5__ {int next; int previous; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  IS_PERSISTENT (size_t) ; 
 scalar_t__ IS_SET (int) ; 
 int NOT_SET ; 

void
cache_bump_bitmap(RDPCLIENT * This, uint8 id, uint16 idx, int bump)
{
	int p_idx, n_idx, n;

	if (!IS_PERSISTENT(id))
		return;

	if (This->cache.bmpcache_mru[id] == idx)
		return;

	DEBUG_RDP5(("bump bitmap: id=%d, idx=%d, bump=%d\n", id, idx, bump));

	n_idx = This->cache.bmpcache[id][idx].next;
	p_idx = This->cache.bmpcache[id][idx].previous;

	if (IS_SET(n_idx))
	{
		/* remove */
		--This->cache.bmpcache_count[id];
		if (IS_SET(p_idx))
			This->cache.bmpcache[id][p_idx].next = n_idx;
		else
			This->cache.bmpcache_lru[id] = n_idx;
		if (IS_SET(n_idx))
			This->cache.bmpcache[id][n_idx].previous = p_idx;
		else
			This->cache.bmpcache_mru[id] = p_idx;
	}
	else
	{
		p_idx = NOT_SET;
		n_idx = This->cache.bmpcache_lru[id];
	}

	if (bump >= 0)
	{
		for (n = 0; n < bump && IS_SET(n_idx); n++)
		{
			p_idx = n_idx;
			n_idx = This->cache.bmpcache[id][p_idx].next;
		}
	}
	else
	{
		p_idx = This->cache.bmpcache_mru[id];
		n_idx = NOT_SET;
	}

	/* insert */
	++This->cache.bmpcache_count[id];
	This->cache.bmpcache[id][idx].previous = p_idx;
	This->cache.bmpcache[id][idx].next = n_idx;

	if (p_idx >= 0)
		This->cache.bmpcache[id][p_idx].next = idx;
	else
		This->cache.bmpcache_lru[id] = idx;

	if (n_idx >= 0)
		This->cache.bmpcache[id][n_idx].previous = idx;
	else
		This->cache.bmpcache_mru[id] = idx;
}