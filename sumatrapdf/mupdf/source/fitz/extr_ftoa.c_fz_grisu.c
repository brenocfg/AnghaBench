#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int e; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int DIY_SIGNIFICAND_SIZE ; 
 TYPE_1__ cached_power (int) ; 
 int digit_gen_mix_grisu2 (TYPE_1__,TYPE_1__,char*,int*) ; 
 int k_comp (int) ; 
 TYPE_1__ minus (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ multiply (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  normalized_boundaries (float,TYPE_1__*,TYPE_1__*) ; 

int
fz_grisu(float v, char* buffer, int* K)
{
	diy_fp_t w_lower, w_upper, D_upper, D_lower, c_mk, delta;
	int length, mk, alpha = -DIY_SIGNIFICAND_SIZE + 4;

	normalized_boundaries(v, &w_lower, &w_upper);
	mk = k_comp(alpha - w_upper.e - DIY_SIGNIFICAND_SIZE);
	c_mk = cached_power(mk);

	D_upper = multiply(w_upper, c_mk);
	D_lower = multiply(w_lower, c_mk);

	D_upper.f--;
	D_lower.f++;

	delta = minus(D_upper, D_lower);

	*K = -mk;
	length = digit_gen_mix_grisu2(D_upper, delta, buffer, K);

	buffer[length] = 0;
	return length;
}