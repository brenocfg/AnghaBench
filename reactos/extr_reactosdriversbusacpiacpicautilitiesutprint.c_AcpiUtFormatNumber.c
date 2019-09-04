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
typedef  int UINT8 ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ INT64 ;
typedef  scalar_t__ INT32 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int ACPI_FORMAT_LEFT ; 
 int ACPI_FORMAT_PREFIX ; 
 int ACPI_FORMAT_SIGN ; 
 int ACPI_FORMAT_SIGN_PLUS ; 
 int ACPI_FORMAT_SIGN_PLUS_SPACE ; 
 int ACPI_FORMAT_UPPER ; 
 int ACPI_FORMAT_ZERO ; 
 scalar_t__ ACPI_PTR_DIFF (char*,char*) ; 
 char* AcpiUtBoundStringOutput (char*,char*,char) ; 
 char* AcpiUtPutNumber (char*,scalar_t__,int,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static char *
AcpiUtFormatNumber (
    char                    *String,
    char                    *End,
    UINT64                  Number,
    UINT8                   Base,
    INT32                   Width,
    INT32                   Precision,
    UINT8                   Type)
{
    char                    *Pos;
    char                    Sign;
    char                    Zero;
    BOOLEAN                 NeedPrefix;
    BOOLEAN                 Upper;
    INT32                   i;
    char                    ReversedString[66];


    /* Parameter validation */

    if (Base < 2 || Base > 16)
    {
        return (NULL);
    }

    if (Type & ACPI_FORMAT_LEFT)
    {
        Type &= ~ACPI_FORMAT_ZERO;
    }

    NeedPrefix = ((Type & ACPI_FORMAT_PREFIX) && Base != 10) ? TRUE : FALSE;
    Upper = (Type & ACPI_FORMAT_UPPER) ? TRUE : FALSE;
    Zero = (Type & ACPI_FORMAT_ZERO) ? '0' : ' ';

    /* Calculate size according to sign and prefix */

    Sign = '\0';
    if (Type & ACPI_FORMAT_SIGN)
    {
        if ((INT64) Number < 0)
        {
            Sign = '-';
            Number = - (INT64) Number;
            Width--;
        }
        else if (Type & ACPI_FORMAT_SIGN_PLUS)
        {
            Sign = '+';
            Width--;
        }
        else if (Type & ACPI_FORMAT_SIGN_PLUS_SPACE)
        {
            Sign = ' ';
            Width--;
        }
    }
    if (NeedPrefix)
    {
        Width--;
        if (Base == 16)
        {
            Width--;
        }
    }

    /* Generate full string in reverse order */

    Pos = AcpiUtPutNumber (ReversedString, Number, Base, Upper);
    i = (INT32) ACPI_PTR_DIFF (Pos, ReversedString);

    /* Printing 100 using %2d gives "100", not "00" */

    if (i > Precision)
    {
        Precision = i;
    }

    Width -= Precision;

    /* Output the string */

    if (!(Type & (ACPI_FORMAT_ZERO | ACPI_FORMAT_LEFT)))
    {
        while (--Width >= 0)
        {
            String = AcpiUtBoundStringOutput (String, End, ' ');
        }
    }
    if (Sign)
    {
        String = AcpiUtBoundStringOutput (String, End, Sign);
    }
    if (NeedPrefix)
    {
        String = AcpiUtBoundStringOutput (String, End, '0');
        if (Base == 16)
        {
            String = AcpiUtBoundStringOutput (
                String, End, Upper ? 'X' : 'x');
        }
    }
    if (!(Type & ACPI_FORMAT_LEFT))
    {
        while (--Width >= 0)
        {
            String = AcpiUtBoundStringOutput (String, End, Zero);
        }
    }

    while (i <= --Precision)
    {
        String = AcpiUtBoundStringOutput (String, End, '0');
    }
    while (--i >= 0)
    {
        String = AcpiUtBoundStringOutput (String, End,
                    ReversedString[i]);
    }
    while (--Width >= 0)
    {
        String = AcpiUtBoundStringOutput (String, End, ' ');
    }

    return (String);
}