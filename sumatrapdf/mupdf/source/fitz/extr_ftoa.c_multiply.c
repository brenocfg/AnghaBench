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
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int DIY_SIGNIFICAND_SIZE ; 

__attribute__((used)) static diy_fp_t
multiply(diy_fp_t x, diy_fp_t y)
{
	uint64_t a, b, c, d, ac, bc, ad, bd, tmp;
	int half = DIY_SIGNIFICAND_SIZE / 2;
	diy_fp_t r; uint64_t mask = ((uint64_t) 1 << half) - 1;
	a = x.f >> half; b = x.f & mask;
	c = y.f >> half; d = y.f & mask;
	ac = a * c; bc = b * c; ad = a * d; bd = b * d;
	tmp = (bd >> half) + (ad & mask) + (bc & mask);
	tmp += ((uint64_t)1U) << (half - 1); /* Round. */
	r.f = ac + (ad >> half) + (bc >> half) + (tmp >> half);
	r.e = x.e + y.e + half * 2;
	return r;
}