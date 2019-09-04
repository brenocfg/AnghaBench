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
#define  VM_REG_GUEST_CS 135 
#define  VM_REG_GUEST_DS 134 
#define  VM_REG_GUEST_ES 133 
#define  VM_REG_GUEST_FS 132 
#define  VM_REG_GUEST_GS 131 
#define  VM_REG_GUEST_LDTR 130 
#define  VM_REG_GUEST_SS 129 
#define  VM_REG_GUEST_TR 128 

__attribute__((used)) static bool
is_segment_register(int reg)
{
	switch (reg) {
	case VM_REG_GUEST_ES:
	case VM_REG_GUEST_CS:
	case VM_REG_GUEST_SS:
	case VM_REG_GUEST_DS:
	case VM_REG_GUEST_FS:
	case VM_REG_GUEST_GS:
	case VM_REG_GUEST_TR:
	case VM_REG_GUEST_LDTR:
		return (TRUE);
	default:
		return (FALSE);
	}
}