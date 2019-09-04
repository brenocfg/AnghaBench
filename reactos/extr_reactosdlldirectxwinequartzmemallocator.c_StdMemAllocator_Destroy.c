#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* DebugInfo; } ;
struct TYPE_7__ {TYPE_4__ csState; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ StdMemAllocator ;
typedef  int /*<<< orphan*/  IMemAllocator ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_4__*) ; 
 TYPE_2__* StdMemAllocator_from_IMemAllocator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void StdMemAllocator_Destroy(IMemAllocator *iface)
{
    StdMemAllocator *This = StdMemAllocator_from_IMemAllocator(iface);

    This->csState.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection(&This->csState);

    CoTaskMemFree(This);
}