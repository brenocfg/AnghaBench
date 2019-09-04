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

/* Variables and functions */

void
src_short_to_float_array (const short *in, float *out, int len)
{
	while (len)
	{	len -- ;
		out [len] = (float) (in [len] / (1.0 * 0x8000)) ;
		} ;

	return ;
}