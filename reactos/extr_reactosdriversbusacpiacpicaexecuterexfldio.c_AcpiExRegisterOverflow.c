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
typedef  int UINT64 ;
struct TYPE_4__ {int BitLength; } ;
struct TYPE_5__ {TYPE_1__ CommonField; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int) ; 
 int ACPI_INTEGER_BIT_SIZE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AcpiExRegisterOverflow (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT64                  Value)
{

    if (ObjDesc->CommonField.BitLength >= ACPI_INTEGER_BIT_SIZE)
    {
        /*
         * The field is large enough to hold the maximum integer, so we can
         * never overflow it.
         */
        return (FALSE);
    }

    if (Value >= ((UINT64) 1 << ObjDesc->CommonField.BitLength))
    {
        /*
         * The Value is larger than the maximum value that can fit into
         * the register.
         */
        ACPI_ERROR ((AE_INFO,
            "Index value 0x%8.8X%8.8X overflows field width 0x%X",
            ACPI_FORMAT_UINT64 (Value),
            ObjDesc->CommonField.BitLength));

        return (TRUE);
    }

    /* The Value will fit into the field with no truncation */

    return (FALSE);
}