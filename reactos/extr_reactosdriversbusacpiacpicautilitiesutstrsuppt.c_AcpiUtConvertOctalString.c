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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IS_OCTAL_DIGIT (char) ; 
 int /*<<< orphan*/  AE_OCTAL_OVERFLOW ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtInsertDigit (int /*<<< orphan*/ *,int,char) ; 

ACPI_STATUS
AcpiUtConvertOctalString (
    char                    *String,
    UINT64                  *ReturnValuePtr)
{
    UINT64                  AccumulatedValue = 0;
    ACPI_STATUS             Status = AE_OK;


    /* Convert each ASCII byte in the input string */

    while (*String)
    {
        /* Character must be ASCII 0-7, otherwise terminate with no error */

        if (!(ACPI_IS_OCTAL_DIGIT (*String)))
        {
            break;
        }

        /* Convert and insert this octal digit into the accumulator */

        Status = AcpiUtInsertDigit (&AccumulatedValue, 8, *String);
        if (ACPI_FAILURE (Status))
        {
            Status = AE_OCTAL_OVERFLOW;
            break;
        }

        String++;
    }

    /* Always return the value that has been accumulated */

    *ReturnValuePtr = AccumulatedValue;
    return (Status);
}