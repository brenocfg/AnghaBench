#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/ * Interrupt; } ;
struct TYPE_6__ {int /*<<< orphan*/  OldIrql; } ;
struct TYPE_7__ {int Lock; TYPE_1__ Context; } ;
typedef  TYPE_2__* PSTOR_LOCK_HANDLE ;
typedef  TYPE_3__* PFDO_DEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
#define  DpcLock 130 
#define  InterruptLock 129 
 int /*<<< orphan*/  KeReleaseInterruptSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  StartIoLock 128 

__attribute__((used)) static
VOID
PortReleaseSpinLock(
    PFDO_DEVICE_EXTENSION DeviceExtension,
    PSTOR_LOCK_HANDLE LockHandle)
{
    DPRINT1("PortReleaseSpinLock(%p %p)\n",
            DeviceExtension, LockHandle);

    switch (LockHandle->Lock)
    {
        case DpcLock: /* 1, */
            DPRINT1("DpcLock\n");
            break;

        case StartIoLock: /* 2 */
            DPRINT1("StartIoLock\n");
            break;

        case InterruptLock: /* 3 */
            DPRINT1("InterruptLock\n");
            if (DeviceExtension->Interrupt != NULL)
                KeReleaseInterruptSpinLock(DeviceExtension->Interrupt,
                                           LockHandle->Context.OldIrql);
            break;
    }
}