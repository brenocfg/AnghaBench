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
typedef  int /*<<< orphan*/  ARM_UDIVRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_udiv_internal (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

ARM_UDIVRESULT
__rt_udiv(
    unsigned int divisor,
    unsigned int dividend)
{
    ARM_UDIVRESULT result;

    __rt_udiv_internal(&result, divisor, dividend);
    return result;
}