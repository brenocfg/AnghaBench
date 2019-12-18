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

/* Variables and functions */
 int* clz_table ; 

__attribute__((used)) static unsigned
leading_zeros (uint32_t x)
{
	unsigned tmp1, tmp2;

	tmp1 = x >> 16;
	if (tmp1)
	{
		tmp2 = tmp1 >> 8;
		if (tmp2)
			return clz_table[tmp2];
		else
			return 8 + clz_table[tmp1];
	}
	else
	{
		tmp1 = x >> 8;
		if (tmp1)
			return 16 + clz_table[tmp1];
		else
			return 24 + clz_table[x];
	}
}