#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WorkQueue ; 
 int /*<<< orphan*/  WorkQueueClear ; 
 int /*<<< orphan*/  WorkQueueDevice ; 
 int /*<<< orphan*/  WorkQueueLock ; 

VOID ChewInit(PDEVICE_OBJECT DeviceObject)
{
    WorkQueueDevice = DeviceObject;
    InitializeListHead(&WorkQueue);
    KeInitializeSpinLock(&WorkQueueLock);
    KeInitializeEvent(&WorkQueueClear, NotificationEvent, TRUE);
}