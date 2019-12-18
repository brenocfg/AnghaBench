#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vmx {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit_qualification; } ;
struct TYPE_4__ {TYPE_1__ vmx; } ;
struct vm_exit {TYPE_2__ u; } ;

/* Variables and functions */
 int APIC_ACCESS_OFFSET (int /*<<< orphan*/ ) ; 
 int APIC_ACCESS_TYPE (int /*<<< orphan*/ ) ; 
#define  APIC_OFFSET_APR 157 
#define  APIC_OFFSET_CMCI_LVT 156 
#define  APIC_OFFSET_IRR0 155 
#define  APIC_OFFSET_IRR1 154 
#define  APIC_OFFSET_IRR2 153 
#define  APIC_OFFSET_IRR3 152 
#define  APIC_OFFSET_IRR4 151 
#define  APIC_OFFSET_IRR5 150 
#define  APIC_OFFSET_IRR6 149 
#define  APIC_OFFSET_IRR7 148 
#define  APIC_OFFSET_ISR0 147 
#define  APIC_OFFSET_ISR1 146 
#define  APIC_OFFSET_ISR2 145 
#define  APIC_OFFSET_ISR3 144 
#define  APIC_OFFSET_ISR4 143 
#define  APIC_OFFSET_ISR5 142 
#define  APIC_OFFSET_ISR6 141 
#define  APIC_OFFSET_ISR7 140 
#define  APIC_OFFSET_PPR 139 
#define  APIC_OFFSET_RRR 138 
#define  APIC_OFFSET_TIMER_CCR 137 
#define  APIC_OFFSET_TMR0 136 
#define  APIC_OFFSET_TMR1 135 
#define  APIC_OFFSET_TMR2 134 
#define  APIC_OFFSET_TMR3 133 
#define  APIC_OFFSET_TMR4 132 
#define  APIC_OFFSET_TMR5 131 
#define  APIC_OFFSET_TMR6 130 
#define  APIC_OFFSET_TMR7 129 
#define  APIC_OFFSET_VER 128 
 scalar_t__ DEFAULT_APIC_BASE ; 
 int UNHANDLED ; 
 int /*<<< orphan*/  VIE_INVALID_GLA ; 
 int /*<<< orphan*/  apic_access_virtualization (struct vmx*,int) ; 
 int /*<<< orphan*/  vmexit_inst_emul (struct vm_exit*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vmx_handle_apic_access(struct vmx *vmx, int vcpuid, struct vm_exit *vmexit)
{
	uint64_t qual;
	int access_type, offset, allowed;

	if (!apic_access_virtualization(vmx, vcpuid))
		return (UNHANDLED);

	qual = vmexit->u.vmx.exit_qualification;
	access_type = APIC_ACCESS_TYPE(qual);
	offset = APIC_ACCESS_OFFSET(qual);

	allowed = 0;
	if (access_type == 0) {
		/*
		 * Read data access to the following registers is expected.
		 */
		switch (offset) {
		case APIC_OFFSET_APR:
		case APIC_OFFSET_PPR:
		case APIC_OFFSET_RRR:
		case APIC_OFFSET_CMCI_LVT:
		case APIC_OFFSET_TIMER_CCR:
			allowed = 1;
			break;
		default:
			break;
		}
	} else if (access_type == 1) {
		/*
		 * Write data access to the following registers is expected.
		 */
		switch (offset) {
		case APIC_OFFSET_VER:
		case APIC_OFFSET_APR:
		case APIC_OFFSET_PPR:
		case APIC_OFFSET_RRR:
		case APIC_OFFSET_ISR0:
		case APIC_OFFSET_ISR1:
		case APIC_OFFSET_ISR2:
		case APIC_OFFSET_ISR3:
		case APIC_OFFSET_ISR4:
		case APIC_OFFSET_ISR5:
		case APIC_OFFSET_ISR6:
		case APIC_OFFSET_ISR7:
		case APIC_OFFSET_TMR0:
		case APIC_OFFSET_TMR1:
		case APIC_OFFSET_TMR2:
		case APIC_OFFSET_TMR3:
		case APIC_OFFSET_TMR4:
		case APIC_OFFSET_TMR5:
		case APIC_OFFSET_TMR6:
		case APIC_OFFSET_TMR7:
		case APIC_OFFSET_IRR0:
		case APIC_OFFSET_IRR1:
		case APIC_OFFSET_IRR2:
		case APIC_OFFSET_IRR3:
		case APIC_OFFSET_IRR4:
		case APIC_OFFSET_IRR5:
		case APIC_OFFSET_IRR6:
		case APIC_OFFSET_IRR7:
		case APIC_OFFSET_CMCI_LVT:
		case APIC_OFFSET_TIMER_CCR:
			allowed = 1;
			break;
		default:
			break;
		}
	}

	if (allowed) {
		vmexit_inst_emul(vmexit, DEFAULT_APIC_BASE + ((uint32_t) offset),
		    VIE_INVALID_GLA, vcpuid);
	}

	/*
	 * Regardless of whether the APIC-access is allowed this handler
	 * always returns UNHANDLED:
	 * - if the access is allowed then it is handled by emulating the
	 *   instruction that caused the VM-exit (outside the critical section)
	 * - if the access is not allowed then it will be converted to an
	 *   exitcode of VM_EXITCODE_VMX and will be dealt with in userland.
	 */
	return (UNHANDLED);
}