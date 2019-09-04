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
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int VCPU_FROZEN ; 
 int VCPU_IDLE ; 
 int VM_MAXCPU ; 
 scalar_t__ vcpu_set_state (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vm ; 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

__attribute__((used)) static void
vcpu_freeze_all(bool freeze)
{
	enum vcpu_state state;
	int vcpu;

	state = (freeze) ? VCPU_FROZEN : VCPU_IDLE;

	for (vcpu = 0; vcpu < VM_MAXCPU; vcpu++) {
		if (vcpu_set_state(vm, vcpu, state, freeze)) {
			xhyve_abort("vcpu_set_state failed\n");
		}
	}
}