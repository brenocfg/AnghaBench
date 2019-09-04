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
struct TYPE_5__ {scalar_t__ SpaceId; TYPE_2__* Next; } ;
struct TYPE_6__ {TYPE_1__ AddressSpace; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  scalar_t__ ACPI_ADR_SPACE_TYPE ;

/* Variables and functions */

ACPI_OPERAND_OBJECT *
AcpiEvFindRegionHandler (
    ACPI_ADR_SPACE_TYPE     SpaceId,
    ACPI_OPERAND_OBJECT     *HandlerObj)
{

    /* Walk the handler list for this device */

    while (HandlerObj)
    {
        /* Same SpaceId indicates a handler is installed */

        if (HandlerObj->AddressSpace.SpaceId == SpaceId)
        {
            return (HandlerObj);
        }

        /* Next handler object */

        HandlerObj = HandlerObj->AddressSpace.Next;
    }

    return (NULL);
}