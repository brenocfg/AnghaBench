#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* ExternalName; char* InternalName; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_NAMESTRING_INFO ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsBuildInternalName (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiNsGetInternalNameLength (TYPE_1__*) ; 
 int /*<<< orphan*/  NsInternalizeName ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiNsInternalizeName (
    const char              *ExternalName,
    char                    **ConvertedName)
{
    char                    *InternalName;
    ACPI_NAMESTRING_INFO    Info;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (NsInternalizeName);


    if ((!ExternalName)      ||
        (*ExternalName == 0) ||
        (!ConvertedName))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Get the length of the new internal name */

    Info.ExternalName = ExternalName;
    AcpiNsGetInternalNameLength (&Info);

    /* We need a segment to store the internal  name */

    InternalName = ACPI_ALLOCATE_ZEROED (Info.Length);
    if (!InternalName)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Build the name */

    Info.InternalName = InternalName;
    Status = AcpiNsBuildInternalName (&Info);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (InternalName);
        return_ACPI_STATUS (Status);
    }

    *ConvertedName = InternalName;
    return_ACPI_STATUS (AE_OK);
}