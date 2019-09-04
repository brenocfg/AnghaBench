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
typedef  size_t UINT8 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int AML_EXTENDED_OPCODE ; 
 int /*<<< orphan*/  const* AcpiGbl_AmlOpInfo ; 
 size_t* AcpiGbl_LongOpIndex ; 
 size_t* AcpiGbl_ShortOpIndex ; 
 size_t MAX_EXTENDED_OPCODE ; 
 int /*<<< orphan*/  OpcodeName ; 
 int /*<<< orphan*/  PsGetOpcodeInfo ; 
 size_t _UNK ; 

const ACPI_OPCODE_INFO *
AcpiPsGetOpcodeInfo (
    UINT16                  Opcode)
{
#ifdef ACPI_DEBUG_OUTPUT
    const char              *OpcodeName = "Unknown AML opcode";
#endif

    ACPI_FUNCTION_NAME (PsGetOpcodeInfo);


    /*
     * Detect normal 8-bit opcode or extended 16-bit opcode
     */
    if (!(Opcode & 0xFF00))
    {
        /* Simple (8-bit) opcode: 0-255, can't index beyond table  */

        return (&AcpiGbl_AmlOpInfo [AcpiGbl_ShortOpIndex [(UINT8) Opcode]]);
    }

    if (((Opcode & 0xFF00) == AML_EXTENDED_OPCODE) &&
        (((UINT8) Opcode) <= MAX_EXTENDED_OPCODE))
    {
        /* Valid extended (16-bit) opcode */

        return (&AcpiGbl_AmlOpInfo [AcpiGbl_LongOpIndex [(UINT8) Opcode]]);
    }

#if defined ACPI_ASL_COMPILER && defined ACPI_DEBUG_OUTPUT
#include "asldefine.h"

    switch (Opcode)
    {
    case AML_RAW_DATA_BYTE:
        OpcodeName = "-Raw Data Byte-";
        break;

    case AML_RAW_DATA_WORD:
        OpcodeName = "-Raw Data Word-";
        break;

    case AML_RAW_DATA_DWORD:
        OpcodeName = "-Raw Data Dword-";
        break;

    case AML_RAW_DATA_QWORD:
        OpcodeName = "-Raw Data Qword-";
        break;

    case AML_RAW_DATA_BUFFER:
        OpcodeName = "-Raw Data Buffer-";
        break;

    case AML_RAW_DATA_CHAIN:
        OpcodeName = "-Raw Data Buffer Chain-";
        break;

    case AML_PACKAGE_LENGTH:
        OpcodeName = "-Package Length-";
        break;

    case AML_UNASSIGNED_OPCODE:
        OpcodeName = "-Unassigned Opcode-";
        break;

    case AML_DEFAULT_ARG_OP:
        OpcodeName = "-Default Arg-";
        break;

    default:
        break;
    }
#endif

    /* Unknown AML opcode */

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "%s [%4.4X]\n", OpcodeName, Opcode));

    return (&AcpiGbl_AmlOpInfo [_UNK]);
}