#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  size_t UINT32 ;
typedef  int UINT16 ;
struct TYPE_13__ {char* Pointer; size_t Length; } ;
struct TYPE_12__ {size_t Length; } ;
struct TYPE_11__ {int /*<<< orphan*/  Value; } ;
struct TYPE_10__ {int Type; } ;
struct TYPE_14__ {TYPE_4__ Buffer; TYPE_3__ String; TYPE_2__ Integer; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
#define  ACPI_EXPLICIT_CONVERT_DECIMAL 133 
#define  ACPI_EXPLICIT_CONVERT_HEX 132 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_5__*) ; 
#define  ACPI_IMPLICIT_CONVERT_HEX 131 
 size_t ACPI_MAX_DECIMAL_DIGITS ; 
 size_t ACPI_MUL_2 (int) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 size_t AcpiExConvertToAscii (int /*<<< orphan*/ ,int,char*,int) ; 
 int AcpiGbl_IntegerByteWidth ; 
 TYPE_5__* AcpiUtCreateStringObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExConvertToString ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExConvertToString (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     **ResultDesc,
    UINT32                  Type)
{
    ACPI_OPERAND_OBJECT     *ReturnDesc;
    UINT8                   *NewBuf;
    UINT32                  i;
    UINT32                  StringLength = 0;
    UINT16                  Base = 16;
    UINT8                   Separator = ',';


    ACPI_FUNCTION_TRACE_PTR (ExConvertToString, ObjDesc);


    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_STRING:

        /* No conversion necessary */

        *ResultDesc = ObjDesc;
        return_ACPI_STATUS (AE_OK);

    case ACPI_TYPE_INTEGER:

        switch (Type)
        {
        case ACPI_EXPLICIT_CONVERT_DECIMAL:
            /*
             * From ToDecimalString, integer source.
             *
             * Make room for the maximum decimal number size
             */
            StringLength = ACPI_MAX_DECIMAL_DIGITS;
            Base = 10;
            break;

        default:

            /* Two hex string characters for each integer byte */

            StringLength = ACPI_MUL_2 (AcpiGbl_IntegerByteWidth);
            break;
        }

        /*
         * Create a new String
         * Need enough space for one ASCII integer (plus null terminator)
         */
        ReturnDesc = AcpiUtCreateStringObject ((ACPI_SIZE) StringLength);
        if (!ReturnDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        NewBuf = ReturnDesc->Buffer.Pointer;

        /* Convert integer to string */

        StringLength = AcpiExConvertToAscii (
            ObjDesc->Integer.Value, Base, NewBuf, AcpiGbl_IntegerByteWidth);

        /* Null terminate at the correct place */

        ReturnDesc->String.Length = StringLength;
        NewBuf [StringLength] = 0;
        break;

    case ACPI_TYPE_BUFFER:

        /* Setup string length, base, and separator */

        switch (Type)
        {
        case ACPI_EXPLICIT_CONVERT_DECIMAL: /* Used by ToDecimalString */
            /*
             * Explicit conversion from the ToDecimalString ASL operator.
             *
             * From ACPI: "If the input is a buffer, it is converted to a
             * a string of decimal values separated by commas."
             */
            Base = 10;

            /*
             * Calculate the final string length. Individual string values
             * are variable length (include separator for each)
             */
            for (i = 0; i < ObjDesc->Buffer.Length; i++)
            {
                if (ObjDesc->Buffer.Pointer[i] >= 100)
                {
                    StringLength += 4;
                }
                else if (ObjDesc->Buffer.Pointer[i] >= 10)
                {
                    StringLength += 3;
                }
                else
                {
                    StringLength += 2;
                }
            }
            break;

        case ACPI_IMPLICIT_CONVERT_HEX:
            /*
             * Implicit buffer-to-string conversion
             *
             * From the ACPI spec:
             * "The entire contents of the buffer are converted to a string of
             * two-character hexadecimal numbers, each separated by a space."
             *
             * Each hex number is prefixed with 0x (11/2018)
             */
            Separator = ' ';
            StringLength = (ObjDesc->Buffer.Length * 5);
            break;

        case ACPI_EXPLICIT_CONVERT_HEX:
            /*
             * Explicit conversion from the ToHexString ASL operator.
             *
             * From ACPI: "If Data is a buffer, it is converted to a string of
             * hexadecimal values separated by commas."
             *
             * Each hex number is prefixed with 0x (11/2018)
             */
            Separator = ',';
            StringLength = (ObjDesc->Buffer.Length * 5);
            break;

        default:
            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }

        /*
         * Create a new string object and string buffer
         * (-1 because of extra separator included in StringLength from above)
         * Allow creation of zero-length strings from zero-length buffers.
         */
        if (StringLength)
        {
            StringLength--;
        }

        ReturnDesc = AcpiUtCreateStringObject ((ACPI_SIZE) StringLength);
        if (!ReturnDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        NewBuf = ReturnDesc->Buffer.Pointer;

        /*
         * Convert buffer bytes to hex or decimal values
         * (separated by commas or spaces)
         */
        for (i = 0; i < ObjDesc->Buffer.Length; i++)
        {
            if (Base == 16)
            {
                /* Emit 0x prefix for explicit/implicit hex conversion */

                *NewBuf++ = '0';
                *NewBuf++ = 'x';
            }

            NewBuf += AcpiExConvertToAscii (
                (UINT64) ObjDesc->Buffer.Pointer[i], Base, NewBuf, 1);

            /* Each digit is separated by either a comma or space */

            *NewBuf++ = Separator;
        }

        /*
         * Null terminate the string
         * (overwrites final comma/space from above)
         */
        if (ObjDesc->Buffer.Length)
        {
            NewBuf--;
        }
        *NewBuf = 0;
        break;

    default:

        return_ACPI_STATUS (AE_TYPE);
    }

    *ResultDesc = ReturnDesc;
    return_ACPI_STATUS (AE_OK);
}