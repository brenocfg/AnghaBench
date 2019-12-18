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
struct vm {int /*<<< orphan*/  cookie; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  stats; int /*<<< orphan*/  guest_xcr0; scalar_t__ exception_pending; scalar_t__ extint_pending; scalar_t__ nmi_pending; scalar_t__ exitintinfo; int /*<<< orphan*/  vlapic; int /*<<< orphan*/  state; int /*<<< orphan*/  vcpu_sleep_cnd; int /*<<< orphan*/  vcpu_sleep_mtx; int /*<<< orphan*/  state_sleep_cnd; int /*<<< orphan*/  state_sleep_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_IDLE ; 
 int /*<<< orphan*/  VLAPIC_INIT (int /*<<< orphan*/ ,int) ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  X2APIC_DISABLED ; 
 int /*<<< orphan*/  XFEATURE_ENABLED_X87 ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_lock_init (struct vcpu*) ; 
 int /*<<< orphan*/  vm_set_x2apic_state (struct vm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_alloc () ; 
 int /*<<< orphan*/  vmm_stat_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcpu_init(struct vm *vm, int vcpu_id, bool create)
{
	struct vcpu *vcpu;

	KASSERT(vcpu_id >= 0 && vcpu_id < VM_MAXCPU,
	    ("vcpu_init: invalid vcpu %d", vcpu_id));
	  
	vcpu = &vm->vcpu[vcpu_id];

	if (create) {
		vcpu_lock_init(vcpu);
		pthread_mutex_init(&vcpu->state_sleep_mtx, NULL);
		pthread_cond_init(&vcpu->state_sleep_cnd, NULL);
		pthread_mutex_init(&vcpu->vcpu_sleep_mtx, NULL);
		pthread_cond_init(&vcpu->vcpu_sleep_cnd, NULL);
		vcpu->state = VCPU_IDLE;
		vcpu->stats = vmm_stat_alloc();
	}

	vcpu->vlapic = VLAPIC_INIT(vm->cookie, vcpu_id);
	vm_set_x2apic_state(vm, vcpu_id, X2APIC_DISABLED);
	vcpu->exitintinfo = 0;
	vcpu->nmi_pending = 0;
	vcpu->extint_pending = 0;
	vcpu->exception_pending = 0;
	vcpu->guest_xcr0 = XFEATURE_ENABLED_X87;
	vmm_stat_init(vcpu->stats);
}