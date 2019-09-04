#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  modulus; int /*<<< orphan*/  quotient; } ;
typedef  int /*<<< orphan*/  ARM_UDIVRESULT ;
typedef  TYPE_1__ ARM_SDIVRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_udiv_internal (int /*<<< orphan*/ *,int,int) ; 

ARM_SDIVRESULT
__rt_sdiv(
    int divisor,
    int dividend)
{
    ARM_SDIVRESULT result;
    int divisor_sign, dividend_sign;

    dividend_sign = divisor & 0x80000000;
    if (dividend_sign)
    {
        dividend = -dividend;
    }

    divisor_sign = divisor & 0x80000000;
    if (divisor_sign)
    {
        divisor = -divisor;
    }

    __rt_udiv_internal((ARM_UDIVRESULT*)&result, divisor, dividend);

    if (dividend_sign ^ divisor_sign)
    {
        result.quotient = -result.quotient;
    }

    if (dividend_sign)
    {
        result.modulus = -result.modulus;
    }

    return result;
}