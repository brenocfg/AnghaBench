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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ ILockBytes_iface; } ;
typedef  TYPE_2__ TestLockBytes ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TestLockBytes_Vtbl ; 

__attribute__((used)) static void CreateTestLockBytes(TestLockBytes **This)
{
    *This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(**This));

    if (*This)
    {
        (*This)->ILockBytes_iface.lpVtbl = &TestLockBytes_Vtbl;
        (*This)->ref = 1;
    }
}