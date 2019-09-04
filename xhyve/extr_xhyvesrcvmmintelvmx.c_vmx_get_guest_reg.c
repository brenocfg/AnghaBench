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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X86_R10 ; 
 int /*<<< orphan*/  HV_X86_R11 ; 
 int /*<<< orphan*/  HV_X86_R12 ; 
 int /*<<< orphan*/  HV_X86_R13 ; 
 int /*<<< orphan*/  HV_X86_R14 ; 
 int /*<<< orphan*/  HV_X86_R15 ; 
 int /*<<< orphan*/  HV_X86_R8 ; 
 int /*<<< orphan*/  HV_X86_R9 ; 
 int /*<<< orphan*/  HV_X86_RAX ; 
 int /*<<< orphan*/  HV_X86_RBP ; 
 int /*<<< orphan*/  HV_X86_RBX ; 
 int /*<<< orphan*/  HV_X86_RCX ; 
 int /*<<< orphan*/  HV_X86_RDI ; 
 int /*<<< orphan*/  HV_X86_RDX ; 
 int /*<<< orphan*/  HV_X86_RSI ; 
 int /*<<< orphan*/  VMCS_GUEST_RSP ; 
 int /*<<< orphan*/  reg_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhyve_abort (char*,int) ; 

__attribute__((used)) static uint64_t
vmx_get_guest_reg(int vcpu, int ident)
{
	switch (ident) {
	case 0:
		return (reg_read(vcpu, HV_X86_RAX));
	case 1:
		return (reg_read(vcpu, HV_X86_RCX));
	case 2:
		return (reg_read(vcpu, HV_X86_RDX));
	case 3:
		return (reg_read(vcpu, HV_X86_RBX));
	case 4:
		return (vmcs_read(vcpu, VMCS_GUEST_RSP));
	case 5:
		return (reg_read(vcpu, HV_X86_RBP));
	case 6:
		return (reg_read(vcpu, HV_X86_RSI));
	case 7:
		return (reg_read(vcpu, HV_X86_RDI));
	case 8:
		return (reg_read(vcpu, HV_X86_R8));
	case 9:
		return (reg_read(vcpu, HV_X86_R9));
	case 10:
		return (reg_read(vcpu, HV_X86_R10));
	case 11:
		return (reg_read(vcpu, HV_X86_R11));
	case 12:
		return (reg_read(vcpu, HV_X86_R12));
	case 13:
		return (reg_read(vcpu, HV_X86_R13));
	case 14:
		return (reg_read(vcpu, HV_X86_R14));
	case 15:
		return (reg_read(vcpu, HV_X86_R15));
	default:
		xhyve_abort("invalid vmx register %d", ident);
	}
}