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
 int SRC_FALSE ; 
 int SRC_TRUE ; 
 scalar_t__ is_bad_src_ratio (double) ; 

int
src_is_valid_ratio (double ratio)
{
	if (is_bad_src_ratio (ratio))
		return SRC_FALSE ;

	return SRC_TRUE ;
}