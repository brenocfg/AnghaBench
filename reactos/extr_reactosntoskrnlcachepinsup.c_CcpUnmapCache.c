#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  ToDeref; int /*<<< orphan*/  ToUnmap; } ;
typedef  TYPE_1__* PWORK_QUEUE_WITH_CONTEXT ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_1__*) ; 
 int /*<<< orphan*/  MmUnmapCacheViewInSystemSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 

VOID
CcpUnmapCache(PVOID Context)
{
    PWORK_QUEUE_WITH_CONTEXT WorkItem = (PWORK_QUEUE_WITH_CONTEXT)Context;
    DPRINT("Unmapping (finally) %x\n", WorkItem->ToUnmap);
    MmUnmapCacheViewInSystemSpace(WorkItem->ToUnmap);
    ObDereferenceObject(WorkItem->ToDeref);
    ExFreePool(WorkItem);
    DPRINT("Done\n");
}