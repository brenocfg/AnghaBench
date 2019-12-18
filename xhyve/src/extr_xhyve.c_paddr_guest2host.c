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
 void* xh_vm_map_gpa (uintptr_t,size_t) ; 

void *
paddr_guest2host(uintptr_t gaddr, size_t len)
{
	return (xh_vm_map_gpa(gaddr, len));
}