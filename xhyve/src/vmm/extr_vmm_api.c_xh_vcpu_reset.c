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
 int CR0_NE ; 
 scalar_t__ SET_DESC (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ SET_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR4 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_IDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_RAX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RCX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  VM_REG_GUEST_TR ; 

int
xh_vcpu_reset(int vcpu)
{
	int error;

#define SET_REG(r, v) (error = xh_vm_set_register(vcpu, (r), (v)))
#define SET_DESC(d, b, l, a) (error = xh_vm_set_desc(vcpu, (d), (b), (l), (a)))

	if (SET_REG(VM_REG_GUEST_RFLAGS, 0x2) ||
		SET_REG(VM_REG_GUEST_RIP, 0xfff0) ||
		SET_REG(VM_REG_GUEST_CR0, CR0_NE) ||
		SET_REG(VM_REG_GUEST_CR3, 0) ||
		SET_REG(VM_REG_GUEST_CR4, 0) ||
		SET_REG(VM_REG_GUEST_CS, 0xf000) ||
		SET_REG(VM_REG_GUEST_SS, 0) ||
		SET_REG(VM_REG_GUEST_DS, 0) ||
		SET_REG(VM_REG_GUEST_ES, 0) ||
		SET_REG(VM_REG_GUEST_FS, 0) ||
		SET_REG(VM_REG_GUEST_GS, 0) ||
		SET_REG(VM_REG_GUEST_RAX, 0) ||
		SET_REG(VM_REG_GUEST_RBX, 0) ||
		SET_REG(VM_REG_GUEST_RCX, 0) ||
		SET_REG(VM_REG_GUEST_RDX, 0xf00) ||
		SET_REG(VM_REG_GUEST_RSI, 0) ||
		SET_REG(VM_REG_GUEST_RDI, 0) ||
		SET_REG(VM_REG_GUEST_RBP, 0) ||
		SET_REG(VM_REG_GUEST_RSP, 0) ||
		SET_REG(VM_REG_GUEST_TR, 0) ||
		SET_REG(VM_REG_GUEST_LDTR, 0) ||
		SET_DESC(VM_REG_GUEST_CS, 0xffff0000, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_SS, 0, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_DS, 0, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_ES, 0, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_FS, 0, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_GS, 0, 0xffff, 0x0093) ||
		SET_DESC(VM_REG_GUEST_GDTR, 0, 0xffff, 0) ||
		SET_DESC(VM_REG_GUEST_IDTR, 0, 0xffff, 0) ||
		SET_DESC(VM_REG_GUEST_TR, 0, 0, 0x0000008b) ||
		SET_DESC(VM_REG_GUEST_LDTR, 0, 0xffff, 0x00000082))
	{
		return (error);
	}

	return (0);
}