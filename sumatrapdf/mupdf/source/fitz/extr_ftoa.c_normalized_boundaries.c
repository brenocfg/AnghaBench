#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int f; int e; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int SP_HIDDEN_BIT ; 
 TYPE_1__ float2diy_fp (float) ; 
 TYPE_1__ normalize_boundary (TYPE_1__) ; 

__attribute__((used)) static void
normalized_boundaries(float f, diy_fp_t* lower_ptr, diy_fp_t* upper_ptr)
{
	diy_fp_t v = float2diy_fp(f);
	diy_fp_t upper, lower;
	int significand_is_zero = v.f == SP_HIDDEN_BIT;

	upper.f = (v.f << 1) + 1; upper.e = v.e - 1;
	upper = normalize_boundary(upper);
	if (significand_is_zero)
	{
		lower.f = (v.f << 2) - 1;
		lower.e = v.e - 2;
	}
	else
	{
		lower.f = (v.f << 1) - 1;
		lower.e = v.e - 1;
	}
	lower.f <<= lower.e - upper.e;
	lower.e = upper.e;

	/* Adjust to double boundaries, so that we can also read the numbers with '(float) strtod'. */
	upper.f -= 1 << 10;
	lower.f += 1 << 10;

	*upper_ptr = upper;
	*lower_ptr = lower;
}