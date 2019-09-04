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
 int HWINTR_BLOCKING ; 
 int /*<<< orphan*/  VMCS_GUEST_INTERRUPTIBILITY ; 
 int /*<<< orphan*/  VMCS_IDENT (int /*<<< orphan*/ ) ; 
 int vmcs_getreg (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
vmx_get_intr_shadow(int vcpu, uint64_t *retval)
{
	uint64_t gi;
	int error;

	error = vmcs_getreg(vcpu, VMCS_IDENT(VMCS_GUEST_INTERRUPTIBILITY), &gi);
	*retval = (gi & HWINTR_BLOCKING) ? 1 : 0;
	return (error);
}