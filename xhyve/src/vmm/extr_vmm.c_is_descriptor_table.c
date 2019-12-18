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
 int FALSE ; 
 int TRUE ; 
#define  VM_REG_GUEST_GDTR 129 
#define  VM_REG_GUEST_IDTR 128 

__attribute__((used)) static bool
is_descriptor_table(int reg)
{
	switch (reg) {
	case VM_REG_GUEST_IDTR:
	case VM_REG_GUEST_GDTR:
		return (TRUE);
	default:
		return (FALSE);
	}
}