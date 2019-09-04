#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct NBNameCache {int /*<<< orphan*/ * head; int /*<<< orphan*/  entryExpireTimeMS; TYPE_2__ cs; scalar_t__ heap; } ;
struct TYPE_3__ {scalar_t__* Spare; } ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ GetProcessHeap () ; 
 struct NBNameCache* HeapAlloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_2__*) ; 

struct NBNameCache *NBNameCacheCreate(HANDLE heap, DWORD entryExpireTimeMS)
{
    struct NBNameCache *cache;
    
    
    if (!heap)
        heap = GetProcessHeap();
    cache = HeapAlloc(heap, 0, sizeof(struct NBNameCache));
    if (cache)
    {
        cache->heap = heap;
        InitializeCriticalSection(&cache->cs);
        cache->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": NBNameCache.cs");
        cache->entryExpireTimeMS = entryExpireTimeMS;
        cache->head = NULL;
    }
    return cache;
}