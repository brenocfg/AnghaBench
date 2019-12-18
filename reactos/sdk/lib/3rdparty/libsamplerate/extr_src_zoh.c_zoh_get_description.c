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
 int SRC_ZERO_ORDER_HOLD ; 

const char*
zoh_get_description (int src_enum)
{
	if (src_enum == SRC_ZERO_ORDER_HOLD)
		return "Zero order hold interpolator, very fast, poor quality." ;

	return NULL ;
}