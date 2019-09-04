#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
struct TYPE_21__ {int /*<<< orphan*/  Flags; TYPE_5__* BufferObj; } ;
struct TYPE_20__ {scalar_t__ Type; int ReferenceCount; } ;
struct TYPE_19__ {scalar_t__ Length; } ;
struct TYPE_18__ {scalar_t__ Value; } ;
struct TYPE_22__ {TYPE_4__ BufferField; TYPE_3__ Common; TYPE_2__ Buffer; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_BIOS_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_5__*) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_BUFFER_LIMIT ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
#define  AML_CREATE_BIT_FIELD_OP 133 
#define  AML_CREATE_BYTE_FIELD_OP 132 
#define  AML_CREATE_DWORD_FIELD_OP 131 
#define  AML_CREATE_FIELD_OP 130 
#define  AML_CREATE_QWORD_FIELD_OP 129 
#define  AML_CREATE_WORD_FIELD_OP 128 
 int /*<<< orphan*/  AML_FIELD_ACCESS_BYTE ; 
 int /*<<< orphan*/  AML_FIELD_ACCESS_DWORD ; 
 int /*<<< orphan*/  AML_FIELD_ACCESS_QWORD ; 
 int /*<<< orphan*/  AML_FIELD_ACCESS_WORD ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiExPrepCommonFieldObject (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (int) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_5__*) ; 
 int /*<<< orphan*/  DsInitBufferField ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsInitBufferField (
    UINT16                  AmlOpcode,
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     *BufferDesc,
    ACPI_OPERAND_OBJECT     *OffsetDesc,
    ACPI_OPERAND_OBJECT     *LengthDesc,
    ACPI_OPERAND_OBJECT     *ResultDesc)
{
    UINT32                  Offset;
    UINT32                  BitOffset;
    UINT32                  BitCount;
    UINT8                   FieldFlags;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (DsInitBufferField, ObjDesc);


    /* Host object must be a Buffer */

    if (BufferDesc->Common.Type != ACPI_TYPE_BUFFER)
    {
        ACPI_ERROR ((AE_INFO,
            "Target of Create Field is not a Buffer object - %s",
            AcpiUtGetObjectTypeName (BufferDesc)));

        Status = AE_AML_OPERAND_TYPE;
        goto Cleanup;
    }

    /*
     * The last parameter to all of these opcodes (ResultDesc) started
     * out as a NameString, and should therefore now be a NS node
     * after resolution in AcpiExResolveOperands().
     */
    if (ACPI_GET_DESCRIPTOR_TYPE (ResultDesc) != ACPI_DESC_TYPE_NAMED)
    {
        ACPI_ERROR ((AE_INFO,
            "(%s) destination not a NS Node [%s]",
            AcpiPsGetOpcodeName (AmlOpcode),
            AcpiUtGetDescriptorName (ResultDesc)));

        Status = AE_AML_OPERAND_TYPE;
        goto Cleanup;
    }

    Offset = (UINT32) OffsetDesc->Integer.Value;

    /*
     * Setup the Bit offsets and counts, according to the opcode
     */
    switch (AmlOpcode)
    {
    case AML_CREATE_FIELD_OP:

        /* Offset is in bits, count is in bits */

        FieldFlags = AML_FIELD_ACCESS_BYTE;
        BitOffset  = Offset;
        BitCount   = (UINT32) LengthDesc->Integer.Value;

        /* Must have a valid (>0) bit count */

        if (BitCount == 0)
        {
            ACPI_BIOS_ERROR ((AE_INFO,
                "Attempt to CreateField of length zero"));
            Status = AE_AML_OPERAND_VALUE;
            goto Cleanup;
        }
        break;

    case AML_CREATE_BIT_FIELD_OP:

        /* Offset is in bits, Field is one bit */

        BitOffset  = Offset;
        BitCount   = 1;
        FieldFlags = AML_FIELD_ACCESS_BYTE;
        break;

    case AML_CREATE_BYTE_FIELD_OP:

        /* Offset is in bytes, field is one byte */

        BitOffset  = 8 * Offset;
        BitCount   = 8;
        FieldFlags = AML_FIELD_ACCESS_BYTE;
        break;

    case AML_CREATE_WORD_FIELD_OP:

        /* Offset is in bytes, field is one word */

        BitOffset  = 8 * Offset;
        BitCount   = 16;
        FieldFlags = AML_FIELD_ACCESS_WORD;
        break;

    case AML_CREATE_DWORD_FIELD_OP:

        /* Offset is in bytes, field is one dword */

        BitOffset  = 8 * Offset;
        BitCount   = 32;
        FieldFlags = AML_FIELD_ACCESS_DWORD;
        break;

    case AML_CREATE_QWORD_FIELD_OP:

        /* Offset is in bytes, field is one qword */

        BitOffset  = 8 * Offset;
        BitCount   = 64;
        FieldFlags = AML_FIELD_ACCESS_QWORD;
        break;

    default:

        ACPI_ERROR ((AE_INFO,
            "Unknown field creation opcode 0x%02X",
            AmlOpcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }

    /* Entire field must fit within the current length of the buffer */

    if ((BitOffset + BitCount) >
        (8 * (UINT32) BufferDesc->Buffer.Length))
    {
        Status = AE_AML_BUFFER_LIMIT;
        ACPI_BIOS_EXCEPTION ((AE_INFO, Status,
            "Field [%4.4s] at bit offset/length %u/%u "
            "exceeds size of target Buffer (%u bits)",
            AcpiUtGetNodeName (ResultDesc), BitOffset, BitCount,
            8 * (UINT32) BufferDesc->Buffer.Length));
        goto Cleanup;
    }

    /*
     * Initialize areas of the field object that are common to all fields
     * For FieldFlags, use LOCK_RULE = 0 (NO_LOCK),
     * UPDATE_RULE = 0 (UPDATE_PRESERVE)
     */
    Status = AcpiExPrepCommonFieldObject (
        ObjDesc, FieldFlags, 0, BitOffset, BitCount);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    ObjDesc->BufferField.BufferObj = BufferDesc;

    /* Reference count for BufferDesc inherits ObjDesc count */

    BufferDesc->Common.ReferenceCount = (UINT16)
        (BufferDesc->Common.ReferenceCount + ObjDesc->Common.ReferenceCount);


Cleanup:

    /* Always delete the operands */

    AcpiUtRemoveReference (OffsetDesc);
    AcpiUtRemoveReference (BufferDesc);

    if (AmlOpcode == AML_CREATE_FIELD_OP)
    {
        AcpiUtRemoveReference (LengthDesc);
    }

    /* On failure, delete the result descriptor */

    if (ACPI_FAILURE (Status))
    {
        AcpiUtRemoveReference (ResultDesc);     /* Result descriptor */
    }
    else
    {
        /* Now the address and length are valid for this BufferField */

        ObjDesc->BufferField.Flags |= AOPOBJ_DATA_VALID;
    }

    return_ACPI_STATUS (Status);
}