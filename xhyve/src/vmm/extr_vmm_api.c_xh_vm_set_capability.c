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
typedef  enum vm_cap_type { ____Placeholder_vm_cap_type } vm_cap_type ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_set_capability (int /*<<< orphan*/ ,int,int,int) ; 

int
xh_vm_set_capability(int vcpu, enum vm_cap_type cap, int val)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_set_capability(vm, vcpu, (int) cap, val);
	vcpu_freeze(vcpu, false);

	return (error);	
}