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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 char* AcpiGbl_LowerHexDigits ; 
 char* AcpiGbl_UpperHexDigits ; 
 int /*<<< orphan*/  AcpiUtDivide (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static char *
AcpiUtPutNumber (
    char                    *String,
    UINT64                  Number,
    UINT8                   Base,
    BOOLEAN                 Upper)
{
    const char              *Digits;
    UINT64                  DigitIndex;
    char                    *Pos;


    Pos = String;
    Digits = Upper ? AcpiGbl_UpperHexDigits : AcpiGbl_LowerHexDigits;

    if (Number == 0)
    {
        *(Pos++) = '0';
    }
    else
    {
        while (Number)
        {
            (void) AcpiUtDivide (Number, Base, &Number, &DigitIndex);
            *(Pos++) = Digits[DigitIndex];
        }
    }

    /* *(Pos++) = '0'; */
    return (Pos);
}