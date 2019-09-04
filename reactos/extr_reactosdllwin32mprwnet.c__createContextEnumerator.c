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
typedef  int /*<<< orphan*/  WNetEnumerator ;
struct TYPE_4__ {void* dwUsage; void* dwType; void* dwScope; int /*<<< orphan*/  enumType; } ;
typedef  TYPE_1__* PWNetEnumerator ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WNET_ENUMERATOR_TYPE_CONTEXT ; 

__attribute__((used)) static PWNetEnumerator _createContextEnumerator(DWORD dwScope, DWORD dwType,
 DWORD dwUsage)
{
    PWNetEnumerator ret = HeapAlloc(GetProcessHeap(),
     HEAP_ZERO_MEMORY, sizeof(WNetEnumerator));

    if (ret)
    {
        ret->enumType = WNET_ENUMERATOR_TYPE_CONTEXT;
        ret->dwScope = dwScope;
        ret->dwType  = dwType;
        ret->dwUsage = dwUsage;
    }
    return ret;
}