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
typedef  int uint32_t ;

/* Variables and functions */
#define  VMCS_GUEST_CR0 129 
#define  VMCS_GUEST_CR4 128 
 int /*<<< orphan*/  vmx_fix_cr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_fix_cr4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
vmcs_fix_regval(uint32_t encoding, uint64_t val)
{

	switch (encoding) {
	case VMCS_GUEST_CR0:
		val = vmx_fix_cr0(val);
		break;
	case VMCS_GUEST_CR4:
		val = vmx_fix_cr4(val);
		break;
	default:
		break;
	}
	return (val);
}