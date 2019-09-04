#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* Mutex; int /*<<< orphan*/  SyncLevel; } ;
struct TYPE_7__ {int /*<<< orphan*/  SyncLevel; int /*<<< orphan*/  OsMutex; } ;
struct TYPE_9__ {TYPE_2__ Method; TYPE_1__ Mutex; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_MUTEX ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiOsCreateMutex (int /*<<< orphan*/ *) ; 
 TYPE_3__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtDeleteObjectDesc (TYPE_3__*) ; 
 int /*<<< orphan*/  DsCreateMethodMutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsCreateMethodMutex (
    ACPI_OPERAND_OBJECT     *MethodDesc)
{
    ACPI_OPERAND_OBJECT     *MutexDesc;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (DsCreateMethodMutex);


    /* Create the new mutex object */

    MutexDesc = AcpiUtCreateInternalObject (ACPI_TYPE_MUTEX);
    if (!MutexDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Create the actual OS Mutex */

    Status = AcpiOsCreateMutex (&MutexDesc->Mutex.OsMutex);
    if (ACPI_FAILURE (Status))
    {
        AcpiUtDeleteObjectDesc (MutexDesc);
        return_ACPI_STATUS (Status);
    }

    MutexDesc->Mutex.SyncLevel = MethodDesc->Method.SyncLevel;
    MethodDesc->Method.Mutex = MutexDesc;
    return_ACPI_STATUS (AE_OK);
}