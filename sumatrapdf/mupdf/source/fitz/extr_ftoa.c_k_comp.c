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

/* Variables and functions */
 int DIY_SIGNIFICAND_SIZE ; 

__attribute__((used)) static int
k_comp(int n)
{
	/* Avoid ceil and floating point multiplication for better
	 * performance and portability. Instead use the approximation
	 * log10(2) ~ 1233/(2^12). Tests show that this gives the correct
	 * result for all values of n in the range -500..500. */
	int tmp = n + DIY_SIGNIFICAND_SIZE - 1;
	int k = (tmp * 1233) / (1 << 12);
	return tmp > 0 ? k + 1 : k;
}