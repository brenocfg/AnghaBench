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
typedef  unsigned long long ULONGLONG ;
typedef  unsigned long long ULONG ;
typedef  int* PULONGLONG ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long long CountLeadingZeros64 (unsigned long long) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static ULONGLONG
UnsignedDivMod128(ULONGLONG DividendLow,
                  ULONGLONG DividendHigh,
                  ULONGLONG Divisor,
                  PULONGLONG QuotientLow,
                  PULONGLONG QuotientHigh)
{
    ULONGLONG ValueLow = DividendLow;
    ULONGLONG ValueHigh = DividendHigh;
    ULONGLONG CurrentLow = 0ULL;
    ULONGLONG CurrentHigh = Divisor;
    ULONG Bits;

    ASSERT(Divisor != 0ULL);

    /* Initialize the quotient */
    *QuotientLow = *QuotientHigh = 0ULL;

    /* Exit early if the dividend is lower than the divisor */
    if ((DividendHigh == 0ULL) && (DividendLow < Divisor)) return ValueLow;

    /* Normalize the current divisor */
    Bits = CountLeadingZeros64(CurrentHigh);
    CurrentHigh <<= Bits;

    while (TRUE)
    {
        /* Shift the quotient left by one bit */
        *QuotientHigh <<= 1;
        *QuotientHigh |= *QuotientLow >> 63;
        *QuotientLow <<= 1;

        /* Check if the value is higher than or equal to the current divisor */
        if ((ValueHigh > CurrentHigh)
            || ((ValueHigh == CurrentHigh) && (ValueLow >= CurrentLow)))
        {
            BOOLEAN Carry = ValueLow < CurrentLow;

            /* Subtract the current divisor from the value */
            ValueHigh -= CurrentHigh;
            ValueLow -= CurrentLow;
            if (Carry) ValueHigh--;

            /* Set the lowest bit of the quotient */
            *QuotientLow |= 1;

            /* Stop if the value is lower than the original divisor */
            if ((ValueHigh == 0ULL) && (ValueLow < Divisor)) break;
        }

        /* Shift the current divisor right by one bit */
        CurrentLow >>= 1;
        CurrentLow |= (CurrentHigh & 1) << 63;
        CurrentHigh >>= 1;
    }

    /*
     * Calculate the number of significant bits the current
     * divisor has more than the original divisor
     */
    Bits = CountLeadingZeros64(Divisor);
    if (CurrentHigh > 0ULL) Bits += 64 - CountLeadingZeros64(CurrentHigh);
    else Bits -= CountLeadingZeros64(CurrentLow);

    if (Bits >= 64)
    {
        *QuotientHigh = *QuotientLow;
        *QuotientLow = 0ULL;
        Bits -= 64;
    }

    if (Bits)
    {
        /* Shift the quotient left by that amount */
        *QuotientHigh <<= Bits;
        *QuotientHigh |= *QuotientLow >> (64 - Bits);
        *QuotientLow <<= Bits;
    }

    /* Return the remainder */
    return ValueLow;
}