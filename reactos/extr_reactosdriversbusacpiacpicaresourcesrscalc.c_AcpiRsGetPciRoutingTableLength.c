#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {scalar_t__ Class; int /*<<< orphan*/  Node; } ;
struct TYPE_9__ {scalar_t__ Length; } ;
struct TYPE_8__ {scalar_t__ Type; } ;
struct TYPE_7__ {scalar_t__ Count; TYPE_5__** Elements; } ;
struct TYPE_11__ {TYPE_4__ Reference; TYPE_3__ String; TYPE_2__ Common; TYPE_1__ Package; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  int /*<<< orphan*/  ACPI_PCI_ROUTING_TABLE ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_REFCLASS_NAME ; 
 scalar_t__ ACPI_ROUND_UP_TO_64BIT (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AcpiNsGetPathnameLength (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RsGetPciRoutingTableLength ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiRsGetPciRoutingTableLength (
    ACPI_OPERAND_OBJECT     *PackageObject,
    ACPI_SIZE               *BufferSizeNeeded)
{
    UINT32                  NumberOfElements;
    ACPI_SIZE               TempSizeNeeded = 0;
    ACPI_OPERAND_OBJECT     **TopObjectList;
    UINT32                  Index;
    ACPI_OPERAND_OBJECT     *PackageElement;
    ACPI_OPERAND_OBJECT     **SubObjectList;
    BOOLEAN                 NameFound;
    UINT32                  TableIndex;


    ACPI_FUNCTION_TRACE (RsGetPciRoutingTableLength);


    NumberOfElements = PackageObject->Package.Count;

    /*
     * Calculate the size of the return buffer.
     * The base size is the number of elements * the sizes of the
     * structures. Additional space for the strings is added below.
     * The minus one is to subtract the size of the UINT8 Source[1]
     * member because it is added below.
     *
     * But each PRT_ENTRY structure has a pointer to a string and
     * the size of that string must be found.
     */
    TopObjectList = PackageObject->Package.Elements;

    for (Index = 0; Index < NumberOfElements; Index++)
    {
        /* Dereference the subpackage */

        PackageElement = *TopObjectList;

        /* We must have a valid Package object */

        if (!PackageElement ||
            (PackageElement->Common.Type != ACPI_TYPE_PACKAGE))
        {
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        /*
         * The SubObjectList will now point to an array of the
         * four IRQ elements: Address, Pin, Source and SourceIndex
         */
        SubObjectList = PackageElement->Package.Elements;

        /* Scan the IrqTableElements for the Source Name String */

        NameFound = FALSE;

        for (TableIndex = 0;
             TableIndex < PackageElement->Package.Count && !NameFound;
             TableIndex++)
        {
            if (*SubObjectList && /* Null object allowed */

                ((ACPI_TYPE_STRING ==
                    (*SubObjectList)->Common.Type) ||

                ((ACPI_TYPE_LOCAL_REFERENCE ==
                    (*SubObjectList)->Common.Type) &&

                    ((*SubObjectList)->Reference.Class ==
                        ACPI_REFCLASS_NAME))))
            {
                NameFound = TRUE;
            }
            else
            {
                /* Look at the next element */

                SubObjectList++;
            }
        }

        TempSizeNeeded += (sizeof (ACPI_PCI_ROUTING_TABLE) - 4);

        /* Was a String type found? */

        if (NameFound)
        {
            if ((*SubObjectList)->Common.Type == ACPI_TYPE_STRING)
            {
                /*
                 * The length String.Length field does not include the
                 * terminating NULL, add 1
                 */
                TempSizeNeeded += ((ACPI_SIZE)
                    (*SubObjectList)->String.Length + 1);
            }
            else
            {
                TempSizeNeeded += AcpiNsGetPathnameLength (
                    (*SubObjectList)->Reference.Node);
            }
        }
        else
        {
            /*
             * If no name was found, then this is a NULL, which is
             * translated as a UINT32 zero.
             */
            TempSizeNeeded += sizeof (UINT32);
        }

        /* Round up the size since each element must be aligned */

        TempSizeNeeded = ACPI_ROUND_UP_TO_64BIT (TempSizeNeeded);

        /* Point to the next ACPI_OPERAND_OBJECT */

        TopObjectList++;
    }

    /*
     * Add an extra element to the end of the list, essentially a
     * NULL terminator
     */
    *BufferSizeNeeded = TempSizeNeeded + sizeof (ACPI_PCI_ROUTING_TABLE);
    return_ACPI_STATUS (AE_OK);
}