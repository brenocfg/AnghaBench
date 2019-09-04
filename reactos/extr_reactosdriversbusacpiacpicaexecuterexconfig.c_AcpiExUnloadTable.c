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
struct TYPE_7__ {scalar_t__ Type; int Flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  Value; } ;
struct TYPE_8__ {TYPE_2__ Common; TYPE_1__ Reference; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_3__*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiExEnterInterpreter () ; 
 int /*<<< orphan*/  AcpiExExitInterpreter () ; 
 int /*<<< orphan*/  AcpiTbUnloadTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExUnloadTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExUnloadTable (
    ACPI_OPERAND_OBJECT     *DdbHandle)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *TableDesc = DdbHandle;
    UINT32                  TableIndex;


    ACPI_FUNCTION_TRACE (ExUnloadTable);


    /*
     * Temporarily emit a warning so that the ASL for the machine can be
     * hopefully obtained. This is to say that the Unload() operator is
     * extremely rare if not completely unused.
     */
    ACPI_WARNING ((AE_INFO,
        "Received request to unload an ACPI table"));

    /*
     * May 2018: Unload is no longer supported for the following reasons:
     * 1) A correct implementation on some hosts may not be possible.
     * 2) Other ACPI implementations do not correctly/fully support it.
     * 3) It requires host device driver support which does not exist.
     *    (To properly support namespace unload out from underneath.)
     * 4) This AML operator has never been seen in the field.
     */
    ACPI_EXCEPTION ((AE_INFO, AE_NOT_IMPLEMENTED,
        "AML Unload operator is not supported"));

    /*
     * Validate the handle
     * Although the handle is partially validated in AcpiExReconfiguration()
     * when it calls AcpiExResolveOperands(), the handle is more completely
     * validated here.
     *
     * Handle must be a valid operand object of type reference. Also, the
     * DdbHandle must still be marked valid (table has not been previously
     * unloaded)
     */
    if ((!DdbHandle) ||
        (ACPI_GET_DESCRIPTOR_TYPE (DdbHandle) != ACPI_DESC_TYPE_OPERAND) ||
        (DdbHandle->Common.Type != ACPI_TYPE_LOCAL_REFERENCE) ||
        (!(DdbHandle->Common.Flags & AOPOBJ_DATA_VALID)))
    {
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /* Get the table index from the DdbHandle */

    TableIndex = TableDesc->Reference.Value;

    /*
     * Release the interpreter lock so that the table lock won't have
     * strict order requirement against it.
     */
    AcpiExExitInterpreter ();
    Status = AcpiTbUnloadTable (TableIndex);
    AcpiExEnterInterpreter ();

    /*
     * Invalidate the handle. We do this because the handle may be stored
     * in a named object and may not be actually deleted until much later.
     */
    if (ACPI_SUCCESS (Status))
    {
        DdbHandle->Common.Flags &= ~AOPOBJ_DATA_VALID;
    }
    return_ACPI_STATUS (Status);
}