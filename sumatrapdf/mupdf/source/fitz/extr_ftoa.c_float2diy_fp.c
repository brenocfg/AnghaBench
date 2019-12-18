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
struct TYPE_3__ {int f; scalar_t__ e; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 scalar_t__ SP_EXPONENT_BIAS ; 
 int SP_EXPONENT_MASK ; 
 int SP_HIDDEN_BIT ; 
 scalar_t__ SP_MIN_EXPONENT ; 
 int SP_SIGNIFICAND_MASK ; 
 int SP_SIGNIFICAND_SIZE ; 
 int float_to_uint32 (float) ; 

__attribute__((used)) static diy_fp_t
float2diy_fp(float d)
{
	uint32_t d32 = float_to_uint32(d);
	int biased_e = (d32 & SP_EXPONENT_MASK) >> SP_SIGNIFICAND_SIZE;
	uint32_t significand = d32 & SP_SIGNIFICAND_MASK;
	diy_fp_t res;

	if (biased_e != 0)
	{
		res.f = significand + SP_HIDDEN_BIT;
		res.e = biased_e - SP_EXPONENT_BIAS;
	}
	else
	{
		res.f = significand;
		res.e = SP_MIN_EXPONENT + 1;
	}
	return res;
}