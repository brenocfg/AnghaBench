#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct vm_guest_paging {int cpu_mode; } ;
struct vie {scalar_t__ num_valid; int num_processed; } ;
struct TYPE_3__ {scalar_t__ gla; scalar_t__ gpa; scalar_t__ cs_base; int cs_d; struct vm_guest_paging paging; struct vie vie; } ;
struct TYPE_4__ {TYPE_1__ inst_emul; } ;
struct vm_exit {int inst_length; scalar_t__ rip; TYPE_2__ u; } ;
struct vm {struct vcpu* vcpu; } ;
struct vcpu {int nextrip; struct vm_exit exitinfo; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int /*<<< orphan*/  mem_region_read_t ;
typedef  enum vm_cpu_mode { ____Placeholder_vm_cpu_mode } vm_cpu_mode ;

/* Variables and functions */
 scalar_t__ DEFAULT_APIC_BASE ; 
 int /*<<< orphan*/  VCPU_CTR1 (struct vm*,int,char*,scalar_t__) ; 
 scalar_t__ VHPET_BASE ; 
 scalar_t__ VHPET_SIZE ; 
 int VIE_INST_SIZE ; 
 scalar_t__ VIOAPIC_BASE ; 
 scalar_t__ VIOAPIC_SIZE ; 
 scalar_t__ XHYVE_PAGE_SIZE ; 
 int /*<<< orphan*/  lapic_mmio_read ; 
 int /*<<< orphan*/  lapic_mmio_write ; 
 int /*<<< orphan*/  vhpet_mmio_read ; 
 int /*<<< orphan*/  vhpet_mmio_write ; 
 int /*<<< orphan*/  vioapic_mmio_read ; 
 int /*<<< orphan*/  vioapic_mmio_write ; 
 scalar_t__ vmm_decode_instruction (struct vm*,int,scalar_t__,int,int,struct vie*) ; 
 int vmm_emulate_instruction (struct vm*,int,scalar_t__,struct vie*,struct vm_guest_paging*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int vmm_fetch_instruction (struct vm*,int,struct vm_guest_paging*,scalar_t__,int,struct vie*,int*) ; 

__attribute__((used)) static int
vm_handle_inst_emul(struct vm *vm, int vcpuid, bool *retu)
{
	struct vie *vie;
	struct vcpu *vcpu;
	struct vm_exit *vme;
	uint64_t gla, gpa, cs_base;
	struct vm_guest_paging *paging;
	mem_region_read_t mread;
	mem_region_write_t mwrite;
	enum vm_cpu_mode cpu_mode;
	int cs_d, error, fault, length;

	vcpu = &vm->vcpu[vcpuid];
	vme = &vcpu->exitinfo;

	gla = vme->u.inst_emul.gla;
	gpa = vme->u.inst_emul.gpa;
	cs_base = vme->u.inst_emul.cs_base;
	cs_d = vme->u.inst_emul.cs_d;
	vie = &vme->u.inst_emul.vie;
	paging = &vme->u.inst_emul.paging;
	cpu_mode = paging->cpu_mode;

	VCPU_CTR1(vm, vcpuid, "inst_emul fault accessing gpa %#llx", gpa);

	/* Fetch, decode and emulate the faulting instruction */
	if (vie->num_valid == 0) {
		/*
		 * If the instruction length is not known then assume a
		 * maximum size instruction.
		 */
		length = vme->inst_length ? vme->inst_length : VIE_INST_SIZE;
		error = vmm_fetch_instruction(vm, vcpuid, paging, vme->rip +
		    cs_base, length, vie, &fault);
	} else {
		/*
		 * The instruction bytes have already been copied into 'vie'
		 */
		error = fault = 0;
	}
	if (error || fault)
		return (error);

	if (vmm_decode_instruction(vm, vcpuid, gla, cpu_mode, cs_d, vie) != 0) {
		VCPU_CTR1(vm, vcpuid, "Error decoding instruction at %#llx",
		    vme->rip + cs_base);
		*retu = true;	    /* dump instruction bytes in userspace */
		return (0);
	}

	/*
	 * If the instruction length was not specified then update it now
	 * along with 'nextrip'.
	 */
	if (vme->inst_length == 0) {
		vme->inst_length = vie->num_processed;
		vcpu->nextrip += vie->num_processed;
	}
 
	/* return to userland unless this is an in-kernel emulated device */
	if (gpa >= DEFAULT_APIC_BASE && gpa < DEFAULT_APIC_BASE + XHYVE_PAGE_SIZE) {
		mread = lapic_mmio_read;
		mwrite = lapic_mmio_write;
	} else if (gpa >= VIOAPIC_BASE && gpa < VIOAPIC_BASE + VIOAPIC_SIZE) {
		mread = vioapic_mmio_read;
		mwrite = vioapic_mmio_write;
	} else if (gpa >= VHPET_BASE && gpa < VHPET_BASE + VHPET_SIZE) {
		mread = vhpet_mmio_read;
		mwrite = vhpet_mmio_write;
	} else {
		*retu = true;
		return (0);
	}

	error = vmm_emulate_instruction(vm, vcpuid, gpa, vie, paging,
	    mread, mwrite, retu);

	return (error);
}