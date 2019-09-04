#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rflags; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_6__ {TYPE_2__ hlt; TYPE_1__ ioapic_eoi; } ;
struct vm_exit {unsigned int rip; TYPE_3__ u; scalar_t__ exitcode; scalar_t__ inst_length; } ;
struct vm {int /*<<< orphan*/  cookie; struct vcpu* vcpu; int /*<<< orphan*/  suspend; int /*<<< orphan*/  rendezvous_func; int /*<<< orphan*/  suspended_cpus; int /*<<< orphan*/  active_cpus; } ;
struct vcpu {unsigned int nextrip; struct vm_exit exitinfo; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (unsigned int,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int PSL_I ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_RUNNING ; 
 int VMRUN (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,void*) ; 
#define  VM_EXITCODE_HLT 137 
#define  VM_EXITCODE_INOUT 136 
#define  VM_EXITCODE_INOUT_STR 135 
#define  VM_EXITCODE_INST_EMUL 134 
#define  VM_EXITCODE_IOAPIC_EOI 133 
#define  VM_EXITCODE_MONITOR 132 
#define  VM_EXITCODE_MWAIT 131 
#define  VM_EXITCODE_PAGING 130 
#define  VM_EXITCODE_RENDEZVOUS 129 
#define  VM_EXITCODE_SUSPENDED 128 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  bcopy (struct vm_exit*,struct vm_exit*,int) ; 
 int /*<<< orphan*/  vcpu_require_state (struct vm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_process_eoi (struct vm*,int,int /*<<< orphan*/ ) ; 
 int vm_handle_hlt (struct vm*,int,int) ; 
 int vm_handle_inout (struct vm*,int,struct vm_exit*,int*) ; 
 int vm_handle_inst_emul (struct vm*,int,int*) ; 
 int /*<<< orphan*/  vm_handle_rendezvous (struct vm*,int) ; 
 int vm_handle_suspend (struct vm*,int,int*) ; 
 int /*<<< orphan*/  vm_inject_ud (struct vm*,int) ; 

int
vm_run(struct vm *vm, int vcpuid, struct vm_exit *vm_exit)
{
	int error;
	struct vcpu *vcpu;
	// uint64_t tscval;
	struct vm_exit *vme;
	bool retu, intr_disabled;
	void *rptr, *sptr;

	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		return (EINVAL);

	if (!CPU_ISSET(((unsigned) vcpuid), &vm->active_cpus))
		return (EINVAL);

	if (CPU_ISSET(((unsigned) vcpuid), &vm->suspended_cpus))
		return (EINVAL);

	rptr = &vm->rendezvous_func;
	sptr = &vm->suspend;
	vcpu = &vm->vcpu[vcpuid];
	vme = &vcpu->exitinfo;
	retu = false;

restart:
	// tscval = rdtsc();

	vcpu_require_state(vm, vcpuid, VCPU_RUNNING);
	error = VMRUN(vm->cookie, vcpuid, (register_t) vcpu->nextrip, rptr, sptr);
	vcpu_require_state(vm, vcpuid, VCPU_FROZEN);


	// vmm_stat_incr(vm, vcpuid, VCPU_TOTAL_RUNTIME, rdtsc() - tscval);

	if (error == 0) {
		retu = false;
		vcpu->nextrip = vme->rip + ((unsigned) vme->inst_length);
		switch (((int) (vme->exitcode))) {
		case VM_EXITCODE_SUSPENDED:
			error = vm_handle_suspend(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_IOAPIC_EOI:
			vioapic_process_eoi(vm, vcpuid,
			    vme->u.ioapic_eoi.vector);
			break;
		case VM_EXITCODE_RENDEZVOUS:
			vm_handle_rendezvous(vm, vcpuid);
			error = 0;
			break;
		case VM_EXITCODE_HLT:
			intr_disabled = ((vme->u.hlt.rflags & PSL_I) == 0);
			error = vm_handle_hlt(vm, vcpuid, intr_disabled);
			break;
		case VM_EXITCODE_PAGING:
			error = 0;
			break;
		case VM_EXITCODE_INST_EMUL:
			error = vm_handle_inst_emul(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_INOUT:
		case VM_EXITCODE_INOUT_STR:
			error = vm_handle_inout(vm, vcpuid, vme, &retu);
			break;
		case VM_EXITCODE_MONITOR:
		case VM_EXITCODE_MWAIT:
			vm_inject_ud(vm, vcpuid);
			break;
		default:
			retu = true;	/* handled in userland */
			break;
		}
	}

	if (error == 0 && retu == false)
		goto restart;

	/* copy the exit information (FIXME: zero copy) */
	bcopy(vme, vm_exit, sizeof(struct vm_exit));
	return (error);
}