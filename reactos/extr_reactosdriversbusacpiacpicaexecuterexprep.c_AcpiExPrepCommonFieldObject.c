#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT8 ;
typedef  void* UINT32 ;
struct TYPE_5__ {void* BaseByteOffset; void* StartFieldBitOffset; void* AccessByteWidth; void* BitLength; void* Attribute; void* FieldFlags; } ;
struct TYPE_6__ {TYPE_1__ CommonField; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DIV_8 (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 void* ACPI_MUL_8 (void*) ; 
 void* ACPI_ROUND_BITS_DOWN_TO_BYTES (void*) ; 
 scalar_t__ ACPI_ROUND_DOWN (void*,void*) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_OK ; 
 void* AcpiExDecodeFieldAccess (TYPE_2__*,void*,void**) ; 
 int /*<<< orphan*/  ExPrepCommonFieldObject ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExPrepCommonFieldObject (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT8                   FieldFlags,
    UINT8                   FieldAttribute,
    UINT32                  FieldBitPosition,
    UINT32                  FieldBitLength)
{
    UINT32                  AccessBitWidth;
    UINT32                  ByteAlignment;
    UINT32                  NearestByteAddress;


    ACPI_FUNCTION_TRACE (ExPrepCommonFieldObject);


    /*
     * Note: the structure being initialized is the
     * ACPI_COMMON_FIELD_INFO;  No structure fields outside of the common
     * area are initialized by this procedure.
     */
    ObjDesc->CommonField.FieldFlags = FieldFlags;
    ObjDesc->CommonField.Attribute  = FieldAttribute;
    ObjDesc->CommonField.BitLength  = FieldBitLength;

    /*
     * Decode the access type so we can compute offsets. The access type gives
     * two pieces of information - the width of each field access and the
     * necessary ByteAlignment (address granularity) of the access.
     *
     * For AnyAcc, the AccessBitWidth is the largest width that is both
     * necessary and possible in an attempt to access the whole field in one
     * I/O operation. However, for AnyAcc, the ByteAlignment is always one
     * byte.
     *
     * For all Buffer Fields, the ByteAlignment is always one byte.
     *
     * For all other access types (Byte, Word, Dword, Qword), the Bitwidth is
     * the same (equivalent) as the ByteAlignment.
     */
    AccessBitWidth = AcpiExDecodeFieldAccess (
        ObjDesc, FieldFlags, &ByteAlignment);
    if (!AccessBitWidth)
    {
        return_ACPI_STATUS (AE_AML_OPERAND_VALUE);
    }

    /* Setup width (access granularity) fields (values are: 1, 2, 4, 8) */

    ObjDesc->CommonField.AccessByteWidth = (UINT8)
        ACPI_DIV_8 (AccessBitWidth);

    /*
     * BaseByteOffset is the address of the start of the field within the
     * region. It is the byte address of the first *datum* (field-width data
     * unit) of the field. (i.e., the first datum that contains at least the
     * first *bit* of the field.)
     *
     * Note: ByteAlignment is always either equal to the AccessBitWidth or 8
     * (Byte access), and it defines the addressing granularity of the parent
     * region or buffer.
     */
    NearestByteAddress =
        ACPI_ROUND_BITS_DOWN_TO_BYTES (FieldBitPosition);
    ObjDesc->CommonField.BaseByteOffset = (UINT32)
        ACPI_ROUND_DOWN (NearestByteAddress, ByteAlignment);

    /*
     * StartFieldBitOffset is the offset of the first bit of the field within
     * a field datum.
     */
    ObjDesc->CommonField.StartFieldBitOffset = (UINT8)
        (FieldBitPosition - ACPI_MUL_8 (ObjDesc->CommonField.BaseByteOffset));

    return_ACPI_STATUS (AE_OK);
}