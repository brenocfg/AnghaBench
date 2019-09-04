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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  AML_RESOURCE_SMALL_HEADER ;
typedef  int /*<<< orphan*/  AML_RESOURCE_LARGE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_GET8 (void*) ; 
 int ACPI_RESOURCE_NAME_LARGE ; 

UINT8
AcpiUtGetResourceHeaderLength (
    void                    *Aml)
{
    ACPI_FUNCTION_ENTRY ();


    /* Examine the large/small bit in the resource header */

    if (ACPI_GET8 (Aml) & ACPI_RESOURCE_NAME_LARGE)
    {
        return (sizeof (AML_RESOURCE_LARGE_HEADER));
    }
    else
    {
        return (sizeof (AML_RESOURCE_SMALL_HEADER));
    }
}