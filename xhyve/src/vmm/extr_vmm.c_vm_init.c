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
struct vm {int /*<<< orphan*/  suspended_cpus; scalar_t__ suspend; int /*<<< orphan*/  active_cpus; int /*<<< orphan*/  vrtc; int /*<<< orphan*/  vpmtmr; int /*<<< orphan*/  vatpit; int /*<<< orphan*/  vatpic; int /*<<< orphan*/  vhpet; int /*<<< orphan*/  vioapic; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_INIT (struct vm*) ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  callout_system_init () ; 
 int /*<<< orphan*/  vatpic_init (struct vm*) ; 
 int /*<<< orphan*/  vatpit_init (struct vm*) ; 
 int /*<<< orphan*/  vcpu_init (struct vm*,int,int) ; 
 int /*<<< orphan*/  vhpet_init (struct vm*) ; 
 int /*<<< orphan*/  vioapic_init (struct vm*) ; 
 int /*<<< orphan*/  vpmtmr_init (struct vm*) ; 
 int /*<<< orphan*/  vrtc_init (struct vm*) ; 

__attribute__((used)) static void
vm_init(struct vm *vm, bool create)
{
	int vcpu;

	if (create) {
		callout_system_init();
	}

	vm->cookie = VM_INIT(vm);
	vm->vioapic = vioapic_init(vm);
	vm->vhpet = vhpet_init(vm);
	vm->vatpic = vatpic_init(vm);
	vm->vatpit = vatpit_init(vm);
	vm->vpmtmr = vpmtmr_init(vm);

	if (create) {
		vm->vrtc = vrtc_init(vm);
	}

	CPU_ZERO(&vm->active_cpus);

	vm->suspend = 0;
	CPU_ZERO(&vm->suspended_cpus);

	for (vcpu = 0; vcpu < VM_MAXCPU; vcpu++) {
		vcpu_init(vm, vcpu, create);
	}
}