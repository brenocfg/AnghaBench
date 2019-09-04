#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {scalar_t__ ThreadId; int AcquisitionDepth; int /*<<< orphan*/ * OwnerThread; scalar_t__ OriginalSyncLevel; int /*<<< orphan*/  OsMutex; } ;
struct TYPE_7__ {TYPE_1__ Mutex; } ;
typedef  scalar_t__ ACPI_THREAD_ID ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvAcquireGlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExSystemWaitMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/  ExAcquireMutexObject ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExAcquireMutexObject (
    UINT16                  Timeout,
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_THREAD_ID          ThreadId)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (ExAcquireMutexObject, ObjDesc);


    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Support for multiple acquires by the owning thread */

    if (ObjDesc->Mutex.ThreadId == ThreadId)
    {
        /*
         * The mutex is already owned by this thread, just increment the
         * acquisition depth
         */
        ObjDesc->Mutex.AcquisitionDepth++;
        return_ACPI_STATUS (AE_OK);
    }

    /* Acquire the mutex, wait if necessary. Special case for Global Lock */

    if (ObjDesc == AcpiGbl_GlobalLockMutex)
    {
        Status = AcpiEvAcquireGlobalLock (Timeout);
    }
    else
    {
        Status = AcpiExSystemWaitMutex (ObjDesc->Mutex.OsMutex, Timeout);
    }

    if (ACPI_FAILURE (Status))
    {
        /* Includes failure from a timeout on TimeDesc */

        return_ACPI_STATUS (Status);
    }

    /* Acquired the mutex: update mutex object */

    ObjDesc->Mutex.ThreadId = ThreadId;
    ObjDesc->Mutex.AcquisitionDepth = 1;
    ObjDesc->Mutex.OriginalSyncLevel = 0;
    ObjDesc->Mutex.OwnerThread = NULL;      /* Used only for AML Acquire() */

    return_ACPI_STATUS (AE_OK);
}