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
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CLEANUP (struct vm*,int) ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  xhyve_abort (char*,int) ; 

void vcpu_destroy(struct vm *vm, int vcpu) {
	if (vcpu < 0 || vcpu >= VM_MAXCPU)
		xhyve_abort("vcpu_destroy: invalid cpuid %d\n", vcpu);

	VCPU_CLEANUP(vm, vcpu);
}