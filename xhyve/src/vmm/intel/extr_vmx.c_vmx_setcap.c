#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vmx {TYPE_1__* cap; } ;
struct TYPE_2__ {int set; scalar_t__ proc_ctls; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ PROCBASED_HLT_EXITING ; 
 scalar_t__ PROCBASED_MTF ; 
 scalar_t__ PROCBASED_PAUSE_EXITING ; 
 scalar_t__ VMCS_PRI_PROC_BASED_CTLS ; 
#define  VM_CAP_HALT_EXIT 130 
#define  VM_CAP_MTRAP_EXIT 129 
#define  VM_CAP_PAUSE_EXIT 128 
 int /*<<< orphan*/  cap_halt_exit ; 
 int /*<<< orphan*/  cap_monitor_trap ; 
 int /*<<< orphan*/  cap_pause_exit ; 
 int /*<<< orphan*/  vmcs_write (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

__attribute__((used)) static int
vmx_setcap(void *arg, int vcpu, int type, int val)
{
	struct vmx *vmx = arg;
	uint32_t baseval;
	uint32_t *pptr;
	uint32_t reg;
	uint32_t flag;
	int retval;

	retval = ENOENT;
	pptr = NULL;
	baseval = 0;
	reg = 0;
	flag = 0;

	switch (type) {
	case VM_CAP_HALT_EXIT:
		if (cap_halt_exit) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_HLT_EXITING;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_MTRAP_EXIT:
		if (cap_monitor_trap) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_MTF;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_PAUSE_EXIT:
		if (cap_pause_exit) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_PAUSE_EXITING;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	default:
		xhyve_abort("vmx_setcap\n");
	}

	if (retval == 0) {
		if (val) {
			baseval |= flag;
		} else {
			baseval &= ~flag;
		}

		vmcs_write(vcpu, reg, baseval);

		/*
		 * Update optional stored flags, and record
		 * setting
		 */
		if (pptr != NULL) {
			*pptr = baseval;
		}

		if (val) {
			vmx->cap[vcpu].set |= (1 << type);
		} else {
			vmx->cap[vcpu].set &= ~(1 << type);
		}

	}

	return (retval);
}