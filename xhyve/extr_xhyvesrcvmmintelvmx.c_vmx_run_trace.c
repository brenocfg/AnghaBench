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
struct vmx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
vmx_run_trace(struct vmx *vmx, int vcpu)
{
#ifdef XHYVE_CONFIG_TRACE
	VCPU_CTR1(vmx->vm, vcpu, "Resume execution at %#llx", vmcs_guest_rip(vcpu));
#else
	(void) vmx;
	(void) vcpu;
#endif
}