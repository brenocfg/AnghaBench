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
typedef  int uint64_t ;

/* Variables and functions */
 int HANDLED ; 
 int UNHANDLED ; 
 int /*<<< orphan*/  VMCS_CR4_SHADOW ; 
 int /*<<< orphan*/  VMCS_GUEST_CR4 ; 
 int cr4_ones_mask ; 
 int cr4_zeros_mask ; 
 int /*<<< orphan*/  vmcs_write (int,int /*<<< orphan*/ ,int) ; 
 int vmx_get_guest_reg (int,int) ; 

__attribute__((used)) static int
vmx_emulate_cr4_access(int vcpu, uint64_t exitqual)
{
	uint64_t crval, regval;

	/* We only handle mov to %cr4 at this time */
	if ((exitqual & 0xf0) != 0x00)
		return (UNHANDLED);

	regval = vmx_get_guest_reg(vcpu, (exitqual >> 8) & 0xf);

	vmcs_write(vcpu, VMCS_CR4_SHADOW, regval);

	crval = regval | cr4_ones_mask;
	crval &= ~cr4_zeros_mask;
	vmcs_write(vcpu, VMCS_GUEST_CR4, crval);

	return (HANDLED);
}