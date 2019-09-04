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
 scalar_t__ CPU_CLIPS_NEGATIVE ; 
 scalar_t__ CPU_CLIPS_POSITIVE ; 
 int lrint (double) ; 

void
src_float_to_short_array (const float *in, short *out, int len)
{	double scaled_value ;

	while (len)
	{	len -- ;

		scaled_value = in [len] * (8.0 * 0x10000000) ;
		if (CPU_CLIPS_POSITIVE == 0 && scaled_value >= (1.0 * 0x7FFFFFFF))
		{	out [len] = 32767 ;
			continue ;
			} ;
		if (CPU_CLIPS_NEGATIVE == 0 && scaled_value <= (-8.0 * 0x10000000))
		{	out [len] = -32768 ;
			continue ;
			} ;

		out [len] = (short) (lrint (scaled_value) >> 16) ;
		} ;

}