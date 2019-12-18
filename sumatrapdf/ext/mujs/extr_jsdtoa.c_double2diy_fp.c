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
typedef  int uint64_t ;
struct TYPE_3__ {int f; scalar_t__ e; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 scalar_t__ DP_EXPONENT_BIAS ; 
 int DP_EXPONENT_MASK ; 
 int DP_HIDDEN_BIT ; 
 scalar_t__ DP_MIN_EXPONENT ; 
 int DP_SIGNIFICAND_MASK ; 
 int DP_SIGNIFICAND_SIZE ; 
 int double_to_uint64 (double) ; 

__attribute__((used)) static diy_fp_t double2diy_fp(double d)
{
	uint64_t d64 = double_to_uint64(d);
	int biased_e = (d64 & DP_EXPONENT_MASK) >> DP_SIGNIFICAND_SIZE;
	uint64_t significand = (d64 & DP_SIGNIFICAND_MASK);
	diy_fp_t res;
	if (biased_e != 0) {
		res.f = significand + DP_HIDDEN_BIT;
		res.e = biased_e - DP_EXPONENT_BIAS;
	} else {
		res.f = significand;
		res.e = DP_MIN_EXPONENT + 1;
	}
	return res;
}