#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Type; } ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_TYPE ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  NsGetType ; 
 int /*<<< orphan*/  return_UINT8 (int /*<<< orphan*/ ) ; 

ACPI_OBJECT_TYPE
AcpiNsGetType (
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_FUNCTION_TRACE (NsGetType);


    if (!Node)
    {
        ACPI_WARNING ((AE_INFO, "Null Node parameter"));
        return_UINT8 (ACPI_TYPE_ANY);
    }

    return_UINT8 (Node->Type);
}