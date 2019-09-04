#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  FullPathname; int /*<<< orphan*/  ReturnFlags; int /*<<< orphan*/  NodeFlags; } ;
struct TYPE_10__ {scalar_t__ Length; char* Pointer; } ;
struct TYPE_9__ {scalar_t__ Type; } ;
struct TYPE_11__ {TYPE_2__ String; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_3__* AcpiUtCreateStringObject (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_3__*) ; 
 int /*<<< orphan*/  NsRepair_HID ; 
 scalar_t__ toupper (int) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_HID (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     *NewString;
    char                    *Source;
    char                    *Dest;


    ACPI_FUNCTION_NAME (NsRepair_HID);


    /* We only care about string _HID objects (not integers) */

    if (ReturnObject->Common.Type != ACPI_TYPE_STRING)
    {
        return (AE_OK);
    }

    if (ReturnObject->String.Length == 0)
    {
        ACPI_WARN_PREDEFINED ((AE_INFO,
            Info->FullPathname, Info->NodeFlags,
            "Invalid zero-length _HID or _CID string"));

        /* Return AE_OK anyway, let driver handle it */

        Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;
        return (AE_OK);
    }

    /* It is simplest to always create a new string object */

    NewString = AcpiUtCreateStringObject (ReturnObject->String.Length);
    if (!NewString)
    {
        return (AE_NO_MEMORY);
    }

    /*
     * Remove a leading asterisk if present. For some unknown reason, there
     * are many machines in the field that contains IDs like this.
     *
     * Examples: "*PNP0C03", "*ACPI0003"
     */
    Source = ReturnObject->String.Pointer;
    if (*Source == '*')
    {
        Source++;
        NewString->String.Length--;

        ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
            "%s: Removed invalid leading asterisk\n", Info->FullPathname));
    }

    /*
     * Copy and uppercase the string. From the ACPI 5.0 specification:
     *
     * A valid PNP ID must be of the form "AAA####" where A is an uppercase
     * letter and # is a hex digit. A valid ACPI ID must be of the form
     * "NNNN####" where N is an uppercase letter or decimal digit, and
     * # is a hex digit.
     */
    for (Dest = NewString->String.Pointer; *Source; Dest++, Source++)
    {
        *Dest = (char) toupper ((int) *Source);
    }

    AcpiUtRemoveReference (ReturnObject);
    *ReturnObjectPtr = NewString;
    return (AE_OK);
}