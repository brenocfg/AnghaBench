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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 int /*<<< orphan*/  AcpiGbl_HardwareLock ; 
 int /*<<< orphan*/  AcpiGbl_NamespaceRwLock ; 
 int /*<<< orphan*/  AcpiGbl_OsiMutex ; 
 int /*<<< orphan*/  AcpiGbl_ReferenceCountLock ; 
 int /*<<< orphan*/  AcpiOsDeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsDeleteMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtDeleteMutex (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtDeleteRwLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtMutexTerminate ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiUtMutexTerminate (
    void)
{
    UINT32                  i;


    ACPI_FUNCTION_TRACE (UtMutexTerminate);


    /* Delete each predefined mutex object */

    for (i = 0; i < ACPI_NUM_MUTEX; i++)
    {
        AcpiUtDeleteMutex (i);
    }

    AcpiOsDeleteMutex (AcpiGbl_OsiMutex);

    /* Delete the spinlocks */

    AcpiOsDeleteLock (AcpiGbl_GpeLock);
    AcpiOsDeleteLock (AcpiGbl_HardwareLock);
    AcpiOsDeleteLock (AcpiGbl_ReferenceCountLock);

    /* Delete the reader/writer lock */

    AcpiUtDeleteRwLock (&AcpiGbl_NamespaceRwLock);
    return_VOID;
}