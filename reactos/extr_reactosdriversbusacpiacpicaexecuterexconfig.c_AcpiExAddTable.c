#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Class; } ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_8__ {TYPE_2__ Reference; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 TYPE_3__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAddTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExAddTable (
    UINT32                  TableIndex,
    ACPI_OPERAND_OBJECT     **DdbHandle)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_TRACE (ExAddTable);


    /* Create an object to be the table handle */

    ObjDesc = AcpiUtCreateInternalObject (ACPI_TYPE_LOCAL_REFERENCE);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Init the table handle */

    ObjDesc->Common.Flags |= AOPOBJ_DATA_VALID;
    ObjDesc->Reference.Class = ACPI_REFCLASS_TABLE;
    ObjDesc->Reference.Value = TableIndex;
    *DdbHandle = ObjDesc;
    return_ACPI_STATUS (AE_OK);
}