#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Flags; struct TYPE_5__* Next; struct TYPE_5__* Name; } ;
typedef  int /*<<< orphan*/  ACPI_STRING ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int ACPI_OSI_DYNAMIC ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,TYPE_1__*) ; 

ACPI_STATUS
AcpiUtRemoveInterface (
    ACPI_STRING             InterfaceName)
{
    ACPI_INTERFACE_INFO     *PreviousInterface;
    ACPI_INTERFACE_INFO     *NextInterface;


    PreviousInterface = NextInterface = AcpiGbl_SupportedInterfaces;
    while (NextInterface)
    {
        if (!strcmp (InterfaceName, NextInterface->Name))
        {
            /*
             * Found: name is in either the static list
             * or was added at runtime
             */
            if (NextInterface->Flags & ACPI_OSI_DYNAMIC)
            {
                /* Interface was added dynamically, remove and free it */

                if (PreviousInterface == NextInterface)
                {
                    AcpiGbl_SupportedInterfaces = NextInterface->Next;
                }
                else
                {
                    PreviousInterface->Next = NextInterface->Next;
                }

                ACPI_FREE (NextInterface->Name);
                ACPI_FREE (NextInterface);
            }
            else
            {
                /*
                 * Interface is in static list. If marked invalid, then
                 * it does not actually exist. Else, mark it invalid.
                 */
                if (NextInterface->Flags & ACPI_OSI_INVALID)
                {
                    return (AE_NOT_EXIST);
                }

                NextInterface->Flags |= ACPI_OSI_INVALID;
            }

            return (AE_OK);
        }

        PreviousInterface = NextInterface;
        NextInterface = NextInterface->Next;
    }

    /* Interface was not found */

    return (AE_NOT_EXIST);
}