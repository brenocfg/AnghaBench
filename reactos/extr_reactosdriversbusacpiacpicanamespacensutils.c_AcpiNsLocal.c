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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  size_t ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_NS_LOCAL ; 
 int ACPI_NS_NORMAL ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int* AcpiGbl_NsProperties ; 
 int /*<<< orphan*/  AcpiUtValidObjectType (size_t) ; 
 int /*<<< orphan*/  NsLocal ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

UINT32
AcpiNsLocal (
    ACPI_OBJECT_TYPE        Type)
{
    ACPI_FUNCTION_TRACE (NsLocal);


    if (!AcpiUtValidObjectType (Type))
    {
        /* Type code out of range  */

        ACPI_WARNING ((AE_INFO, "Invalid Object Type 0x%X", Type));
        return_UINT32 (ACPI_NS_NORMAL);
    }

    return_UINT32 (AcpiGbl_NsProperties[Type] & ACPI_NS_LOCAL);
}