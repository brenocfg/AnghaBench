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
struct vm_guest_paging {int /*<<< orphan*/  paging_mode; int /*<<< orphan*/  cpu_mode; int /*<<< orphan*/  cpl; int /*<<< orphan*/  cr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmcs_guest_cr3 (int) ; 
 int /*<<< orphan*/  vmx_cpl (int) ; 
 int /*<<< orphan*/  vmx_cpu_mode (int) ; 
 int /*<<< orphan*/  vmx_paging_mode (int) ; 

__attribute__((used)) static void
vmx_paging_info(struct vm_guest_paging *paging, int vcpu)
{
	paging->cr3 = vmcs_guest_cr3(vcpu);
	paging->cpl = vmx_cpl(vcpu);
	paging->cpu_mode = vmx_cpu_mode(vcpu);
	paging->paging_mode = vmx_paging_mode(vcpu);
}