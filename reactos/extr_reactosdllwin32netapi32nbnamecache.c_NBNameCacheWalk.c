#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct NBNameCache {TYPE_2__* head; } ;
struct TYPE_6__ {scalar_t__ expireTime; struct TYPE_6__* next; TYPE_1__* entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ NBNameCacheNode ;

/* Variables and functions */
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  NBNameCacheUnlinkNode (struct NBNameCache*,TYPE_2__**) ; 
 scalar_t__ NCBNAMSZ ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static NBNameCacheNode **NBNameCacheWalk(struct NBNameCache *cache,
 const char name[NCBNAMSZ])
{
    NBNameCacheNode **ret = NULL;

    if (cache && cache->head)
    {
        NBNameCacheNode **ptr;

        ptr = &cache->head;
        while (ptr && *ptr && (*ptr)->entry)
        {
            if (!memcmp((*ptr)->entry->name, name, NCBNAMSZ - 1))
                ret = ptr;
            else
            {
                if (GetTickCount() > (*ptr)->expireTime)
                    NBNameCacheUnlinkNode(cache, ptr);
            }
            if (*ptr)
                ptr = &(*ptr)->next;
        }
    }
    return ret;
}