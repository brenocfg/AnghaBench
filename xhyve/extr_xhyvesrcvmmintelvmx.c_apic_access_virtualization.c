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
typedef  int uint32_t ;
struct vmx {TYPE_1__* cap; } ;
struct TYPE_2__ {int proc_ctls2; } ;

/* Variables and functions */
 int PROCBASED2_VIRTUALIZE_APIC_ACCESSES ; 

__attribute__((used)) static __inline int
apic_access_virtualization(struct vmx *vmx, int vcpuid)
{
	uint32_t proc_ctls2;

	proc_ctls2 = vmx->cap[vcpuid].proc_ctls2;
	return ((proc_ctls2 & PROCBASED2_VIRTUALIZE_APIC_ACCESSES) ? 1 : 0);
}