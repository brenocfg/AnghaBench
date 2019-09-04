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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {TYPE_1__* XruptBlock; struct TYPE_6__* Previous; struct TYPE_6__* Next; } ;
struct TYPE_5__ {TYPE_2__* GpeBlockListHead; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GPE_XRUPT_INFO ;
typedef  TYPE_2__ ACPI_GPE_BLOCK_INFO ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_EVENTS ; 
 int /*<<< orphan*/  AcpiEvGetGpeXruptBlock (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvInstallGpeBlock ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiEvInstallGpeBlock (
    ACPI_GPE_BLOCK_INFO     *GpeBlock,
    UINT32                  InterruptNumber)
{
    ACPI_GPE_BLOCK_INFO     *NextGpeBlock;
    ACPI_GPE_XRUPT_INFO     *GpeXruptBlock;
    ACPI_STATUS             Status;
    ACPI_CPU_FLAGS          Flags;


    ACPI_FUNCTION_TRACE (EvInstallGpeBlock);


    Status = AcpiUtAcquireMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiEvGetGpeXruptBlock (InterruptNumber, &GpeXruptBlock);
    if (ACPI_FAILURE (Status))
    {
        goto UnlockAndExit;
    }

    /* Install the new block at the end of the list with lock */

    Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);
    if (GpeXruptBlock->GpeBlockListHead)
    {
        NextGpeBlock = GpeXruptBlock->GpeBlockListHead;
        while (NextGpeBlock->Next)
        {
            NextGpeBlock = NextGpeBlock->Next;
        }

        NextGpeBlock->Next = GpeBlock;
        GpeBlock->Previous = NextGpeBlock;
    }
    else
    {
        GpeXruptBlock->GpeBlockListHead = GpeBlock;
    }

    GpeBlock->XruptBlock = GpeXruptBlock;
    AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);


UnlockAndExit:
    (void) AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
    return_ACPI_STATUS (Status);
}