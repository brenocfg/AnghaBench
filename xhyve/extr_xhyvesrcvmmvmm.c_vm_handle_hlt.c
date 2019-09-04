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
struct vm {int /*<<< orphan*/  halted_cpus; int /*<<< orphan*/  active_cpus; scalar_t__ suspend; int /*<<< orphan*/ * rendezvous_func; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  vcpu_sleep_mtx; int /*<<< orphan*/  vcpu_sleep_cnd; int /*<<< orphan*/  vlapic; } ;
struct timespec {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR0 (struct vm*,int,char*) ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_SLEEPING ; 
 int /*<<< orphan*/  VM_SUSPEND_HALT ; 
 scalar_t__ halt_detection_enabled ; 
 int /*<<< orphan*/  pthread_cond_timedwait_relative_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_require_state_locked (struct vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 
 scalar_t__ vlapic_pending_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_extint_pending (struct vm*,int) ; 
 scalar_t__ vm_nmi_pending (struct vm*,int) ; 
 int /*<<< orphan*/  vm_suspend (struct vm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vm_handle_hlt(struct vm *vm, int vcpuid, bool intr_disabled)
{
	struct vcpu *vcpu;
	const char *wmesg;
	int vcpu_halted, vm_halted;
	const struct timespec ts = {.tv_sec = 1, .tv_nsec = 0}; /* 1 second */

	KASSERT(!CPU_ISSET(((unsigned) vcpuid), &vm->halted_cpus),
		("vcpu already halted"));

	vcpu = &vm->vcpu[vcpuid];
	vcpu_halted = 0;
	vm_halted = 0;

	vcpu_lock(vcpu);
	while (1) {
		/*
		 * Do a final check for pending NMI or interrupts before
		 * really putting this thread to sleep. Also check for
		 * software events that would cause this vcpu to wakeup.
		 *
		 * These interrupts/events could have happened after the
		 * vcpu returned from VMRUN() and before it acquired the
		 * vcpu lock above.
		 */
		if (vm->rendezvous_func != NULL || vm->suspend)
			break;
		if (vm_nmi_pending(vm, vcpuid))
			break;
		if (!intr_disabled) {
			if (vm_extint_pending(vm, vcpuid) ||
			    vlapic_pending_intr(vcpu->vlapic, NULL)) {
				break;
			}
		}

		/*
		 * Some Linux guests implement "halt" by having all vcpus
		 * execute HLT with interrupts disabled. 'halted_cpus' keeps
		 * track of the vcpus that have entered this state. When all
		 * vcpus enter the halted state the virtual machine is halted.
		 */
		if (intr_disabled) {
			wmesg = "vmhalt";
			VCPU_CTR0(vm, vcpuid, "Halted");
			if (!vcpu_halted && halt_detection_enabled) {
				vcpu_halted = 1;
				CPU_SET_ATOMIC(((unsigned) vcpuid), &vm->halted_cpus);
			}
			if (CPU_CMP(&vm->halted_cpus, &vm->active_cpus) == 0) {
				vm_halted = 1;
				break;
			}
		} else {
			wmesg = "vmidle";
		}

		//t = ticks;
		vcpu_require_state_locked(vcpu, VCPU_SLEEPING);
		/*
		 * XXX msleep_spin() cannot be interrupted by signals so
		 * wake up periodically to check pending signals.
		 */
		pthread_mutex_lock(&vcpu->vcpu_sleep_mtx);
		vcpu_unlock(vcpu);
		pthread_cond_timedwait_relative_np(&vcpu->vcpu_sleep_cnd,
			&vcpu->vcpu_sleep_mtx, &ts);
		vcpu_lock(vcpu);
		pthread_mutex_unlock(&vcpu->vcpu_sleep_mtx);
		//msleep_spin(vcpu, &vcpu->mtx, wmesg, hz);
		vcpu_require_state_locked(vcpu, VCPU_FROZEN);
		//vmm_stat_incr(vm, vcpuid, VCPU_IDLE_TICKS, ticks - t);
	}

	if (vcpu_halted)
		CPU_CLR_ATOMIC(((unsigned) vcpuid), &vm->halted_cpus);

	vcpu_unlock(vcpu);

	if (vm_halted)
		vm_suspend(vm, VM_SUSPEND_HALT);

	return (0);
}