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
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Event; int /*<<< orphan*/  CurrentUnits; } ;
typedef  TYPE_1__* PACPI_SEM ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__* ACPI_SEMAPHORE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiOsSignalSemaphore(
    ACPI_SEMAPHORE Handle,
    UINT32 Units)
{
    PACPI_SEM Sem = Handle;
    KIRQL OldIrql;

    if (!Handle)
    {
        DPRINT1("Bad parameter\n");
        return AE_BAD_PARAMETER;
    }

    KeAcquireSpinLock(&Sem->Lock, &OldIrql);

    Sem->CurrentUnits += Units;
    KeSetEvent(&Sem->Event, IO_NO_INCREMENT, FALSE);

    KeReleaseSpinLock(&Sem->Lock, OldIrql);

    return AE_OK;
}