#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  GpeBlock; } ;
struct TYPE_5__ {TYPE_1__ Device; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;
typedef  int /*<<< orphan*/  ACPI_GPE_EVENT_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_MAX_GPE_BLOCKS ; 
 int /*<<< orphan*/ * AcpiEvLowGetGpeInfo (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AcpiGbl_GpeFadtBlocks ; 
 TYPE_2__* AcpiNsGetAttachedObject (int /*<<< orphan*/ *) ; 

ACPI_GPE_EVENT_INFO *
AcpiEvGetGpeEventInfo (
    ACPI_HANDLE             GpeDevice,
    UINT32                  GpeNumber)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_GPE_EVENT_INFO     *GpeInfo;
    UINT32                  i;


    ACPI_FUNCTION_ENTRY ();


    /* A NULL GpeDevice means use the FADT-defined GPE block(s) */

    if (!GpeDevice)
    {
        /* Examine GPE Block 0 and 1 (These blocks are permanent) */

        for (i = 0; i < ACPI_MAX_GPE_BLOCKS; i++)
        {
            GpeInfo = AcpiEvLowGetGpeInfo (GpeNumber,
                AcpiGbl_GpeFadtBlocks[i]);
            if (GpeInfo)
            {
                return (GpeInfo);
            }
        }

        /* The GpeNumber was not in the range of either FADT GPE block */

        return (NULL);
    }

    /* A Non-NULL GpeDevice means this is a GPE Block Device */

    ObjDesc = AcpiNsGetAttachedObject ((ACPI_NAMESPACE_NODE *) GpeDevice);
    if (!ObjDesc ||
        !ObjDesc->Device.GpeBlock)
    {
        return (NULL);
    }

    return (AcpiEvLowGetGpeInfo (GpeNumber, ObjDesc->Device.GpeBlock));
}