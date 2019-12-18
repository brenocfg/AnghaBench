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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  strtof_fp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 float INFINITY ; 
 int /*<<< orphan*/  divide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float diy_to_float (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strtof_cached_power (int) ; 
 int /*<<< orphan*/  strtof_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint32_to_diy (int) ; 

__attribute__((used)) static float
scale_integer_to_float(uint32_t M, int N, int negative)
{
	strtof_fp_t result, x, power;

	if (M == 0)
		return negative ? -0.f : 0.f;
	if (N > 38)
	{
		/* Overflow.  */
		errno = ERANGE;
		return negative ? -INFINITY : INFINITY;
	}
	if (N < -54)
	{
		/* Underflow.  */
		errno = ERANGE;
		return negative ? -0.f : 0.f;
	}
	/* If N is in the range {-13, ..., 13} the conversion is exact.
	   Try to scale N into this region.  */
	while (N > 13 && M <= 0xffffffff / 10)
	{
		M *= 10;
		--N;
	}

	while (N < -13 && M % 10 == 0)
	{
		M /= 10;
		++N;
	}

	x = uint32_to_diy (M);
	if (N >= 0)
	{
		power = strtof_cached_power(N);
		result = strtof_multiply(x, power);
	}
	else
	{
		power = strtof_cached_power(-N);
		result = divide(x, power);
	}

	return diy_to_float(result, negative);
}