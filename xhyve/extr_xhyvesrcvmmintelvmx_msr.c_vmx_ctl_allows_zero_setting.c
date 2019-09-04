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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool
vmx_ctl_allows_zero_setting(uint64_t msr_val, int bitpos)
{
	if ((msr_val & (1UL << bitpos)) == 0)
		return (TRUE);
	else
		return (FALSE);
}