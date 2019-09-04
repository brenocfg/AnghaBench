#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Pointer; } ;
struct TYPE_7__ {int /*<<< orphan*/  Type; } ;
struct TYPE_9__ {TYPE_2__ String; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_3__* AcpiUtCreateStringObject (scalar_t__) ; 
 char* AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExConvertToObjectTypeString (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     **ResultDesc)
{
    ACPI_OPERAND_OBJECT     *ReturnDesc;
    const char              *TypeString;


    TypeString = AcpiUtGetTypeName (ObjDesc->Common.Type);

    ReturnDesc = AcpiUtCreateStringObject (
        ((ACPI_SIZE) strlen (TypeString) + 9)); /* 9 For "[ Object]" */
    if (!ReturnDesc)
    {
        return (AE_NO_MEMORY);
    }

    strcpy (ReturnDesc->String.Pointer, "[");
    strcat (ReturnDesc->String.Pointer, TypeString);
    strcat (ReturnDesc->String.Pointer, " Object]");

    *ResultDesc = ReturnDesc;
    return (AE_OK);
}