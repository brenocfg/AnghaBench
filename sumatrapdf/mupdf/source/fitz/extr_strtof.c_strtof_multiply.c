#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int f; scalar_t__ e; } ;
typedef  TYPE_1__ strtof_fp_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static strtof_fp_t
strtof_multiply(strtof_fp_t x, strtof_fp_t y)
{
	uint64_t tmp;
	strtof_fp_t res;

	assert(x.f & y.f & 0x80000000);

	res.e = x.e + y.e + 32;
	tmp = (uint64_t) x.f * y.f;
	/* Normalize.  */
	if ((tmp < ((uint64_t) 1 << 63)))
	{
		tmp <<= 1;
		--res.e;
	}

	res.f = tmp >> 32;

	/* Set the last bit of the significand to 1 if the result is
	   inexact. */
	if (tmp & 0xffffffff)
		res.f |= 1;
	return res;
}