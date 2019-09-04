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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */

const char *
AcpiPsGetOpcodeName (
    UINT16                  Opcode)
{
#if defined(ACPI_DISASSEMBLER) || defined (ACPI_DEBUG_OUTPUT)

    const ACPI_OPCODE_INFO  *Op;


    Op = AcpiPsGetOpcodeInfo (Opcode);

    /* Always guaranteed to return a valid pointer */

    return (Op->Name);

#else
    return ("OpcodeName unavailable");

#endif
}