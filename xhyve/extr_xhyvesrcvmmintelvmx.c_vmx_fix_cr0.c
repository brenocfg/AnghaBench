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
typedef  int u_long ;

/* Variables and functions */
 int cr0_ones_mask ; 
 int cr0_zeros_mask ; 

u_long
vmx_fix_cr0(u_long cr0)
{
	return ((cr0 | cr0_ones_mask) & ~cr0_zeros_mask);
}