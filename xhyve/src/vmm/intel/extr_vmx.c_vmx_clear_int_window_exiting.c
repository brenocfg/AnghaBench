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
struct vmx {int /*<<< orphan*/  vm; TYPE_1__* cap; } ;
struct TYPE_2__ {int proc_ctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PROCBASED_INT_WINDOW_EXITING ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCS_PRI_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  vmcs_write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __inline
vmx_clear_int_window_exiting(struct vmx *vmx, int vcpu)
{
	KASSERT((vmx->cap[vcpu].proc_ctls & PROCBASED_INT_WINDOW_EXITING) != 0,
	    ("intr_window_exiting not set: %#x", vmx->cap[vcpu].proc_ctls));
	vmx->cap[vcpu].proc_ctls &= ~PROCBASED_INT_WINDOW_EXITING;
	vmcs_write(vcpu, VMCS_PRI_PROC_BASED_CTLS, vmx->cap[vcpu].proc_ctls);
	VCPU_CTR0(vmx->vm, vcpu, "Disabling interrupt window exiting");
}