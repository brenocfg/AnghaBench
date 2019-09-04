#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_7__ {size_t Type; } ;
struct TYPE_9__ {TYPE_1__ CommonSerialBus; } ;
struct TYPE_8__ {size_t Type; TYPE_4__ Data; int /*<<< orphan*/  Length; } ;
typedef  TYPE_2__ ACPI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_IS_DEBUG_ENABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LV_RESOURCES ; 
 TYPE_2__* ACPI_NEXT_RESOURCE (TYPE_2__*) ; 
 size_t ACPI_RESOURCE_TYPE_END_TAG ; 
 size_t ACPI_RESOURCE_TYPE_MAX ; 
 size_t ACPI_RESOURCE_TYPE_SERIAL_BUS ; 
 int /*<<< orphan*/ * AcpiGbl_DumpResourceDispatch ; 
 int /*<<< orphan*/ * AcpiGbl_DumpSerialBusDispatch ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiRsDumpDescriptor (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _COMPONENT ; 

void
AcpiRsDumpResourceList (
    ACPI_RESOURCE           *ResourceList)
{
    UINT32                  Count = 0;
    UINT32                  Type;


    ACPI_FUNCTION_ENTRY ();


    /* Check if debug output enabled */

    if (!ACPI_IS_DEBUG_ENABLED (ACPI_LV_RESOURCES, _COMPONENT))
    {
        return;
    }

    /* Walk list and dump all resource descriptors (END_TAG terminates) */

    do
    {
        AcpiOsPrintf ("\n[%02X] ", Count);
        Count++;

        /* Validate Type before dispatch */

        Type = ResourceList->Type;
        if (Type > ACPI_RESOURCE_TYPE_MAX)
        {
            AcpiOsPrintf (
                "Invalid descriptor type (%X) in resource list\n",
                ResourceList->Type);
            return;
        }

        /* Sanity check the length. It must not be zero, or we loop forever */

        if (!ResourceList->Length)
        {
            AcpiOsPrintf (
                "Invalid zero length descriptor in resource list\n");
            return;
        }

        /* Dump the resource descriptor */

        if (Type == ACPI_RESOURCE_TYPE_SERIAL_BUS)
        {
            AcpiRsDumpDescriptor (&ResourceList->Data,
                AcpiGbl_DumpSerialBusDispatch[
                    ResourceList->Data.CommonSerialBus.Type]);
        }
        else
        {
            AcpiRsDumpDescriptor (&ResourceList->Data,
                AcpiGbl_DumpResourceDispatch[Type]);
        }

        /* Point to the next resource structure */

        ResourceList = ACPI_NEXT_RESOURCE (ResourceList);

        /* Exit when END_TAG descriptor is reached */

    } while (Type != ACPI_RESOURCE_TYPE_END_TAG);
}