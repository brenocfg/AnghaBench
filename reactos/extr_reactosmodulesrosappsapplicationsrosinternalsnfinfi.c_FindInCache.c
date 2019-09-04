#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONGLONG ;
struct TYPE_4__ {scalar_t__ MftId; struct TYPE_4__* Next; } ;
typedef  TYPE_1__* PNAME_CACHE_ENTRY ;

/* Variables and functions */
 TYPE_1__* CacheHead ; 

PNAME_CACHE_ENTRY FindInCache(ULONGLONG MftId)
{
    PNAME_CACHE_ENTRY CacheEntry;

    for (CacheEntry = CacheHead; CacheEntry != NULL; CacheEntry = CacheEntry->Next)
    {
        if (MftId == CacheEntry->MftId)
        {
            return CacheEntry;
        }
    }

    return NULL;
}