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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_UINT64_MAX ; 
 int /*<<< orphan*/  AE_NUMERIC_OVERFLOW ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiGbl_IntegerBitWidth ; 
 int /*<<< orphan*/  AcpiUtShortDivide (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtStrtoulMultiply64 (
    UINT64                  Multiplicand,
    UINT32                  Base,
    UINT64                  *OutProduct)
{
    UINT64                  Product;
    UINT64                  Quotient;


    /* Exit if either operand is zero */

    *OutProduct = 0;
    if (!Multiplicand || !Base)
    {
        return (AE_OK);
    }

    /*
     * Check for 64-bit overflow before the actual multiplication.
     *
     * Notes: 64-bit division is often not supported on 32-bit platforms
     * (it requires a library function), Therefore ACPICA has a local
     * 64-bit divide function. Also, Multiplier is currently only used
     * as the radix (8/10/16), to the 64/32 divide will always work.
     */
    AcpiUtShortDivide (ACPI_UINT64_MAX, Base, &Quotient, NULL);
    if (Multiplicand > Quotient)
    {
        return (AE_NUMERIC_OVERFLOW);
    }

    Product = Multiplicand * Base;

    /* Check for 32-bit overflow if necessary */

    if ((AcpiGbl_IntegerBitWidth == 32) && (Product > ACPI_UINT32_MAX))
    {
        return (AE_NUMERIC_OVERFLOW);
    }

    *OutProduct = Product;
    return (AE_OK);
}