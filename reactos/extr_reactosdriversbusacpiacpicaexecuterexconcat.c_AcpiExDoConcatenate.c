#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int Type; } ;
struct TYPE_22__ {scalar_t__ Length; int /*<<< orphan*/ * Pointer; } ;
struct TYPE_21__ {char* Pointer; scalar_t__ Length; } ;
struct TYPE_20__ {int /*<<< orphan*/  Value; } ;
struct TYPE_24__ {TYPE_4__ Common; TYPE_3__ Buffer; TYPE_2__ String; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;
typedef  int ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERSION ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERT_HEX ; 
 int /*<<< orphan*/  ACPI_MUL_2 (scalar_t__) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExConvertToBuffer (TYPE_5__*,TYPE_5__**) ; 
 int /*<<< orphan*/  AcpiExConvertToInteger (TYPE_5__*,TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExConvertToObjectTypeString (TYPE_5__*,TYPE_5__**) ; 
 int /*<<< orphan*/  AcpiExConvertToString (TYPE_5__*,TYPE_5__**,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiGbl_IntegerByteWidth ; 
 TYPE_5__* AcpiUtCreateBufferObject (scalar_t__) ; 
 TYPE_5__* AcpiUtCreateStringObject (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_5__*) ; 
 int /*<<< orphan*/  ExDoConcatenate ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

ACPI_STATUS
AcpiExDoConcatenate (
    ACPI_OPERAND_OBJECT     *Operand0,
    ACPI_OPERAND_OBJECT     *Operand1,
    ACPI_OPERAND_OBJECT     **ActualReturnDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     *LocalOperand0 = Operand0;
    ACPI_OPERAND_OBJECT     *LocalOperand1 = Operand1;
    ACPI_OPERAND_OBJECT     *TempOperand1 = NULL;
    ACPI_OPERAND_OBJECT     *ReturnDesc;
    char                    *Buffer;
    ACPI_OBJECT_TYPE        Operand0Type;
    ACPI_OBJECT_TYPE        Operand1Type;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (ExDoConcatenate);


    /* Operand 0 preprocessing */

    switch (Operand0->Common.Type)
    {
    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_STRING:
    case ACPI_TYPE_BUFFER:

        Operand0Type = Operand0->Common.Type;
        break;

    default:

        /* For all other types, get the "object type" string */

        Status = AcpiExConvertToObjectTypeString (
            Operand0, &LocalOperand0);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        Operand0Type = ACPI_TYPE_STRING;
        break;
    }

    /* Operand 1 preprocessing */

    switch (Operand1->Common.Type)
    {
    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_STRING:
    case ACPI_TYPE_BUFFER:

        Operand1Type = Operand1->Common.Type;
        break;

    default:

        /* For all other types, get the "object type" string */

        Status = AcpiExConvertToObjectTypeString (
            Operand1, &LocalOperand1);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        Operand1Type = ACPI_TYPE_STRING;
        break;
    }

    /*
     * Convert the second operand if necessary. The first operand (0)
     * determines the type of the second operand (1) (See the Data Types
     * section of the ACPI specification). Both object types are
     * guaranteed to be either Integer/String/Buffer by the operand
     * resolution mechanism.
     */
    switch (Operand0Type)
    {
    case ACPI_TYPE_INTEGER:

        Status = AcpiExConvertToInteger (LocalOperand1, &TempOperand1,
            ACPI_IMPLICIT_CONVERSION);
        break;

    case ACPI_TYPE_BUFFER:

        Status = AcpiExConvertToBuffer (LocalOperand1, &TempOperand1);
        break;

    case ACPI_TYPE_STRING:

        switch (Operand1Type)
        {
        case ACPI_TYPE_INTEGER:
        case ACPI_TYPE_STRING:
        case ACPI_TYPE_BUFFER:

            /* Other types have already been converted to string */

            Status = AcpiExConvertToString (
                LocalOperand1, &TempOperand1, ACPI_IMPLICIT_CONVERT_HEX);
            break;

        default:

            Status = AE_OK;
            break;
        }
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Invalid object type: 0x%X",
            Operand0->Common.Type));
        Status = AE_AML_INTERNAL;
    }

    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* Take care with any newly created operand objects */

    if ((LocalOperand1 != Operand1) &&
        (LocalOperand1 != TempOperand1))
    {
        AcpiUtRemoveReference (LocalOperand1);
    }

    LocalOperand1 = TempOperand1;

    /*
     * Both operands are now known to be the same object type
     * (Both are Integer, String, or Buffer), and we can now perform
     * the concatenation.
     *
     * There are three cases to handle, as per the ACPI spec:
     *
     * 1) Two Integers concatenated to produce a new Buffer
     * 2) Two Strings concatenated to produce a new String
     * 3) Two Buffers concatenated to produce a new Buffer
     */
    switch (Operand0Type)
    {
    case ACPI_TYPE_INTEGER:

        /* Result of two Integers is a Buffer */
        /* Need enough buffer space for two integers */

        ReturnDesc = AcpiUtCreateBufferObject (
            (ACPI_SIZE) ACPI_MUL_2 (AcpiGbl_IntegerByteWidth));
        if (!ReturnDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        Buffer = (char *) ReturnDesc->Buffer.Pointer;

        /* Copy the first integer, LSB first */

        memcpy (Buffer, &Operand0->Integer.Value,
            AcpiGbl_IntegerByteWidth);

        /* Copy the second integer (LSB first) after the first */

        memcpy (Buffer + AcpiGbl_IntegerByteWidth,
            &LocalOperand1->Integer.Value, AcpiGbl_IntegerByteWidth);
        break;

    case ACPI_TYPE_STRING:

        /* Result of two Strings is a String */

        ReturnDesc = AcpiUtCreateStringObject (
            ((ACPI_SIZE) LocalOperand0->String.Length +
            LocalOperand1->String.Length));
        if (!ReturnDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        Buffer = ReturnDesc->String.Pointer;

        /* Concatenate the strings */

        strcpy (Buffer, LocalOperand0->String.Pointer);
        strcat (Buffer, LocalOperand1->String.Pointer);
        break;

    case ACPI_TYPE_BUFFER:

        /* Result of two Buffers is a Buffer */

        ReturnDesc = AcpiUtCreateBufferObject (
            ((ACPI_SIZE) Operand0->Buffer.Length +
            LocalOperand1->Buffer.Length));
        if (!ReturnDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        Buffer = (char *) ReturnDesc->Buffer.Pointer;

        /* Concatenate the buffers */

        memcpy (Buffer, Operand0->Buffer.Pointer,
            Operand0->Buffer.Length);
        memcpy (Buffer + Operand0->Buffer.Length,
            LocalOperand1->Buffer.Pointer,
            LocalOperand1->Buffer.Length);
        break;

    default:

        /* Invalid object type, should not happen here */

        ACPI_ERROR ((AE_INFO, "Invalid object type: 0x%X",
            Operand0->Common.Type));
        Status = AE_AML_INTERNAL;
        goto Cleanup;
    }

    *ActualReturnDesc = ReturnDesc;

Cleanup:
    if (LocalOperand0 != Operand0)
    {
        AcpiUtRemoveReference (LocalOperand0);
    }

    if (LocalOperand1 != Operand1)
    {
        AcpiUtRemoveReference (LocalOperand1);
    }

    return_ACPI_STATUS (Status);
}