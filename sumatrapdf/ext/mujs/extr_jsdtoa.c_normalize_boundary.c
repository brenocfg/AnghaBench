#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int f; scalar_t__ e; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int DIY_SIGNIFICAND_SIZE ; 
 int DP_HIDDEN_BIT ; 
 int DP_SIGNIFICAND_SIZE ; 

__attribute__((used)) static diy_fp_t normalize_boundary(diy_fp_t in)
{
	diy_fp_t res = in;
	/* Normalize now */
	/* the original number could have been a denormal. */
	while (! (res.f & (DP_HIDDEN_BIT << 1))) {
		res.f <<= 1;
		res.e--;
	}
	/* do the final shifts in one go. Don't forget the hidden bit (the '-1') */
	res.f <<= (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
	res.e = res.e - (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
	return res;
}