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
struct vm_exit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_run (int /*<<< orphan*/ ,int,struct vm_exit*) ; 

int
xh_vm_run(int vcpu, struct vm_exit *ret_vmexit)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_run(vm, vcpu, ret_vmexit);
	vcpu_freeze(vcpu, false);

	return (error);
}