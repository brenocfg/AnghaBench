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
typedef  scalar_t__ UINT64 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtShortDivide (scalar_t__,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExDigitsNeeded ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

__attribute__((used)) static UINT32
AcpiExDigitsNeeded (
    UINT64                  Value,
    UINT32                  Base)
{
    UINT32                  NumDigits;
    UINT64                  CurrentValue;


    ACPI_FUNCTION_TRACE (ExDigitsNeeded);


    /* UINT64 is unsigned, so we don't worry about a '-' prefix */

    if (Value == 0)
    {
        return_UINT32 (1);
    }

    CurrentValue = Value;
    NumDigits = 0;

    /* Count the digits in the requested base */

    while (CurrentValue)
    {
        (void) AcpiUtShortDivide (CurrentValue, Base, &CurrentValue, NULL);
        NumDigits++;
    }

    return_UINT32 (NumDigits);
}