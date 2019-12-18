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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMCS_GUEST_CR0 ; 
 int /*<<< orphan*/  VMCS_GUEST_CR3 ; 
 int /*<<< orphan*/  VMCS_GUEST_CR4 ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_DR7 ; 
 int /*<<< orphan*/  VMCS_GUEST_DS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_ES_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_FS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_GS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_IA32_EFER ; 
 int /*<<< orphan*/  VMCS_GUEST_LDTR_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_PDPTE0 ; 
 int /*<<< orphan*/  VMCS_GUEST_PDPTE1 ; 
 int /*<<< orphan*/  VMCS_GUEST_PDPTE2 ; 
 int /*<<< orphan*/  VMCS_GUEST_PDPTE3 ; 
 int /*<<< orphan*/  VMCS_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VMCS_GUEST_RIP ; 
 int /*<<< orphan*/  VMCS_GUEST_RSP ; 
 int /*<<< orphan*/  VMCS_GUEST_SS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_GUEST_TR_SELECTOR ; 
#define  VM_REG_GUEST_CR0 147 
#define  VM_REG_GUEST_CR3 146 
#define  VM_REG_GUEST_CR4 145 
#define  VM_REG_GUEST_CS 144 
#define  VM_REG_GUEST_DR7 143 
#define  VM_REG_GUEST_DS 142 
#define  VM_REG_GUEST_EFER 141 
#define  VM_REG_GUEST_ES 140 
#define  VM_REG_GUEST_FS 139 
#define  VM_REG_GUEST_GS 138 
#define  VM_REG_GUEST_LDTR 137 
#define  VM_REG_GUEST_PDPTE0 136 
#define  VM_REG_GUEST_PDPTE1 135 
#define  VM_REG_GUEST_PDPTE2 134 
#define  VM_REG_GUEST_PDPTE3 133 
#define  VM_REG_GUEST_RFLAGS 132 
#define  VM_REG_GUEST_RIP 131 
#define  VM_REG_GUEST_RSP 130 
#define  VM_REG_GUEST_SS 129 
#define  VM_REG_GUEST_TR 128 

__attribute__((used)) static uint32_t
vmcs_field_encoding(int ident)
{
	switch (ident) {
	case VM_REG_GUEST_CR0:
		return (VMCS_GUEST_CR0);
	case VM_REG_GUEST_CR3:
		return (VMCS_GUEST_CR3);
	case VM_REG_GUEST_CR4:
		return (VMCS_GUEST_CR4);
	case VM_REG_GUEST_DR7:
		return (VMCS_GUEST_DR7);
	case VM_REG_GUEST_RSP:
		return (VMCS_GUEST_RSP);
	case VM_REG_GUEST_RIP:
		return (VMCS_GUEST_RIP);
	case VM_REG_GUEST_RFLAGS:
		return (VMCS_GUEST_RFLAGS);
	case VM_REG_GUEST_ES:
		return (VMCS_GUEST_ES_SELECTOR);
	case VM_REG_GUEST_CS:
		return (VMCS_GUEST_CS_SELECTOR);
	case VM_REG_GUEST_SS:
		return (VMCS_GUEST_SS_SELECTOR);
	case VM_REG_GUEST_DS:
		return (VMCS_GUEST_DS_SELECTOR);
	case VM_REG_GUEST_FS:
		return (VMCS_GUEST_FS_SELECTOR);
	case VM_REG_GUEST_GS:
		return (VMCS_GUEST_GS_SELECTOR);
	case VM_REG_GUEST_TR:
		return (VMCS_GUEST_TR_SELECTOR);
	case VM_REG_GUEST_LDTR:
		return (VMCS_GUEST_LDTR_SELECTOR);
	case VM_REG_GUEST_EFER:
		return (VMCS_GUEST_IA32_EFER);
	case VM_REG_GUEST_PDPTE0:
		return (VMCS_GUEST_PDPTE0);
	case VM_REG_GUEST_PDPTE1:
		return (VMCS_GUEST_PDPTE1);
	case VM_REG_GUEST_PDPTE2:
		return (VMCS_GUEST_PDPTE2);
	case VM_REG_GUEST_PDPTE3:
		return (VMCS_GUEST_PDPTE3);
	default:
		return ((uint32_t) -1);
	}

}