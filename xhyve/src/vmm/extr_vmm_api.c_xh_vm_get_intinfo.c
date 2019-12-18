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

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_get_intinfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xh_vm_get_intinfo(int vcpu, uint64_t *i1, uint64_t *i2)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_get_intinfo(vm, vcpu, i1, i2);
	vcpu_freeze(vcpu, false);

	return (error);	
}