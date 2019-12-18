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
typedef  int uint32_t ;
struct TYPE_3__ {int f; int e; } ;
typedef  TYPE_1__ strtof_fp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int SP_SIGNIFICAND_MASK ; 
 int SP_SIGNIFICAND_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static float
diy_to_float(strtof_fp_t x, int negative)
{
	uint32_t result;
	union
	{
		float f;
		uint32_t n;
	} tmp;

	assert(x.f & 0x80000000);

	/* We have 2^32 - 2^7 = 0xffffff80.  */
	if (x.e > 96 || (x.e == 96 && x.f >= 0xffffff80))
	{
		/* Overflow. Set result to infinity.  */
		errno = ERANGE;
		result = 0xff << SP_SIGNIFICAND_SIZE;
	}
	/* We have 2^32 - 2^8 = 0xffffff00.  */
	else if (x.e > -158)
	{
		/* x is greater or equal to FLT_MAX. So we get a normalized number. */
		result = (uint32_t) (x.e + 158) << SP_SIGNIFICAND_SIZE;
		result |= (x.f >> 8) & SP_SIGNIFICAND_MASK;

		if (x.f & 0x80)
		{
			/* Round-bit is set.  */
			if (x.f & 0x7f)
				/* Sticky-bit is set.  */
				++result;
			else if (x.f & 0x100)
				/* Significand is odd.  */
				++result;
		}
	}
	else if (x.e == -158 && x.f >= 0xffffff00)
	{
		/* x is in the range (2^32, 2^32 - 2^8] * 2^-158, so its smaller than
		   FLT_MIN but still rounds to it. */
		result = 1U << SP_SIGNIFICAND_SIZE;
	}
	else if (x.e > -181)
	{
		/* Non-zero Denormal.  */
		int shift = -149 - x.e; 	/* 9 <= shift <= 31.  */

		result = x.f >> shift;

		if (x.f & (1U << (shift - 1)))
			/* Round-bit is set.  */
		{
			if (x.f & ((1U << (shift - 1)) - 1))
				/* Sticky-bit is set.  */
				++result;
			else if (x.f & 1U << shift)
				/* Significand is odd. */
				++result;
		}
	}
	else if (x.e == -181 && x.f > 0x80000000)
	{
		/* x is in the range (0.5,1) *  2^-149 so it rounds to the smallest
		   denormal. Can't handle this in the previous case as shifting a
		   uint32_t 32 bits to the right is undefined behaviour.  */
		result = 1;
	}
	else
	{
		/* Underflow. */
		errno = ERANGE;
		result = 0;
	}

	if (negative)
		result |= 0x80000000;

	tmp.n = result;
	return tmp.f;
}