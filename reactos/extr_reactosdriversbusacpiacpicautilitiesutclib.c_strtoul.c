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
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 int ACPI_SIGN_NEGATIVE ; 
 int ACPI_SIGN_POSITIVE ; 
 int ACPI_UINT32_MAX ; 
 scalar_t__ AE_ERROR ; 
 scalar_t__ AE_OK ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ isupper (int) ; 
 char tolower (char const) ; 
 scalar_t__ toupper (char const) ; 

UINT32
strtoul (
    const char              *String,
    char                    **Terminator,
    UINT32                  Base)
{
    UINT32                  converted = 0;
    UINT32                  index;
    UINT32                  sign;
    const char              *StringStart;
    UINT32                  ReturnValue = 0;
    ACPI_STATUS             Status = AE_OK;


    /*
     * Save the value of the pointer to the buffer's first
     * character, save the current errno value, and then
     * skip over any white space in the buffer:
     */
    StringStart = String;
    while (isspace (*String) || *String == '\t')
    {
        ++String;
    }

    /*
     * The buffer may contain an optional plus or minus sign.
     * If it does, then skip over it but remember what is was:
     */
    if (*String == '-')
    {
        sign = ACPI_SIGN_NEGATIVE;
        ++String;
    }
    else if (*String == '+')
    {
        ++String;
        sign = ACPI_SIGN_POSITIVE;
    }
    else
    {
        sign = ACPI_SIGN_POSITIVE;
    }

    /*
     * If the input parameter Base is zero, then we need to
     * determine if it is octal, decimal, or hexadecimal:
     */
    if (Base == 0)
    {
        if (*String == '0')
        {
            if (tolower (*(++String)) == 'x')
            {
                Base = 16;
                ++String;
            }
            else
            {
                Base = 8;
            }
        }
        else
        {
            Base = 10;
        }
    }
    else if (Base < 2 || Base > 36)
    {
        /*
         * The specified Base parameter is not in the domain of
         * this function:
         */
        goto done;
    }

    /*
     * For octal and hexadecimal bases, skip over the leading
     * 0 or 0x, if they are present.
     */
    if (Base == 8 && *String == '0')
    {
        String++;
    }

    if (Base == 16 &&
        *String == '0' &&
        tolower (*(++String)) == 'x')
    {
        String++;
    }

    /*
     * Main loop: convert the string to an unsigned long:
     */
    while (*String)
    {
        if (isdigit (*String))
        {
            index = (UINT32) ((UINT8) *String - '0');
        }
        else
        {
            index = (UINT32) toupper (*String);
            if (isupper (index))
            {
                index = index - 'A' + 10;
            }
            else
            {
                goto done;
            }
        }

        if (index >= Base)
        {
            goto done;
        }

        /*
         * Check to see if value is out of range:
         */

        if (ReturnValue > ((ACPI_UINT32_MAX - (UINT32) index) /
                            (UINT32) Base))
        {
            Status = AE_ERROR;
            ReturnValue = 0;           /* reset */
        }
        else
        {
            ReturnValue *= Base;
            ReturnValue += index;
            converted = 1;
        }

        ++String;
    }

done:
    /*
     * If appropriate, update the caller's pointer to the next
     * unconverted character in the buffer.
     */
    if (Terminator)
    {
        if (converted == 0 && ReturnValue == 0 && String != NULL)
        {
            *Terminator = (char *) StringStart;
        }
        else
        {
            *Terminator = (char *) String;
        }
    }

    if (Status == AE_ERROR)
    {
        ReturnValue = ACPI_UINT32_MAX;
    }

    /*
     * If a minus sign was present, then "the conversion is negated":
     */
    if (sign == ACPI_SIGN_NEGATIVE)
    {
        ReturnValue = (ACPI_UINT32_MAX - ReturnValue) + 1;
    }

    return (ReturnValue);
}