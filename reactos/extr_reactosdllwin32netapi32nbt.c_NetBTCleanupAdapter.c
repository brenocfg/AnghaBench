#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nameCache; } ;
typedef  TYPE_1__ NetBTAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  NBNameCacheDestroy (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 

__attribute__((used)) static void NetBTCleanupAdapter(void *adapt)
{
    TRACE("adapt %p\n", adapt);
    if (adapt)
    {
        NetBTAdapter *adapter = adapt;

        if (adapter->nameCache)
            NBNameCacheDestroy(adapter->nameCache);
        HeapFree(GetProcessHeap(), 0, adapt);
    }
}