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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
vmx_exit_trace(struct vmx *vmx, int vcpu, uint64_t rip, uint32_t exit_reason,
	       int handled)
{
#ifdef XHYVE_CONFIG_TRACE
	VCPU_CTR3(vmx->vm, vcpu, "%s %s vmexit at 0x%0llx",
		 handled ? "handled" : "unhandled",
		 exit_reason_to_str((int) exit_reason), rip);
#else
	(void) vmx;
	(void) vcpu;
	(void) rip;
	(void) exit_reason;
	(void) handled;
#endif
}