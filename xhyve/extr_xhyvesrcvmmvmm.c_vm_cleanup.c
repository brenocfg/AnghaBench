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
struct vm {int num_mem_segs; int /*<<< orphan*/ * mem_segs; int /*<<< orphan*/  cookie; int /*<<< orphan*/  vioapic; int /*<<< orphan*/  vatpic; int /*<<< orphan*/  vhpet; int /*<<< orphan*/  vatpit; int /*<<< orphan*/  vpmtmr; int /*<<< orphan*/  vrtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_CLEANUP (int /*<<< orphan*/ ) ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  vatpic_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vatpit_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_cleanup (struct vm*,int,int) ; 
 int /*<<< orphan*/  vhpet_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_free_mem_seg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpmtmr_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrtc_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrtc_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_cleanup(struct vm *vm, bool destroy)
{
	int i, vcpu;

	for (vcpu = 0; vcpu < VM_MAXCPU; vcpu++) {
		vcpu_cleanup(vm, vcpu, destroy);
	}

	if (destroy) {
		vrtc_cleanup(vm->vrtc);
	} else {
		vrtc_reset(vm->vrtc);
	}
	vpmtmr_cleanup(vm->vpmtmr);
	vatpit_cleanup(vm->vatpit);
	vhpet_cleanup(vm->vhpet);
	vatpic_cleanup(vm->vatpic);
	vioapic_cleanup(vm->vioapic);

	VM_CLEANUP(vm->cookie);

	if (destroy) {
		for (i = 0; i < vm->num_mem_segs; i++) {
			vm_free_mem_seg(&vm->mem_segs[i]);
		}

		vm->num_mem_segs = 0;
	}
}