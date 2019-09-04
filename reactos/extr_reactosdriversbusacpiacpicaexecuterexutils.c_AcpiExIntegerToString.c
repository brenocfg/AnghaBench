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
typedef  size_t UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t AcpiExDigitsNeeded (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AcpiUtShortDivide (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*) ; 

void
AcpiExIntegerToString (
    char                    *OutString,
    UINT64                  Value)
{
    UINT32                  Count;
    UINT32                  DigitsNeeded;
    UINT32                  Remainder;


    ACPI_FUNCTION_ENTRY ();


    DigitsNeeded = AcpiExDigitsNeeded (Value, 10);
    OutString[DigitsNeeded] = 0;

    for (Count = DigitsNeeded; Count > 0; Count--)
    {
        (void) AcpiUtShortDivide (Value, 10, &Value, &Remainder);
        OutString[Count-1] = (char) ('0' + Remainder);\
    }
}