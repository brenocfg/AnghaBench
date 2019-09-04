#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ paging_mode; int cr3; int cpl; } ;
struct vm_task_switch {scalar_t__ reason; TYPE_1__ paging; } ;
struct tss32 {int tss_eflags; int tss_ldt; unsigned int tss_cr3; int tss_eip; int tss_eax; int tss_ecx; int tss_edx; int tss_ebx; int tss_esp; int tss_ebp; int tss_esi; int tss_edi; int tss_es; int tss_cs; int tss_ss; int tss_ds; int tss_fs; int tss_gs; int /*<<< orphan*/  tss_link; } ;
struct seg_desc {int dummy; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGING_MODE_FLAT ; 
 scalar_t__ PAGING_MODE_PAE ; 
 int PSL_NT ; 
 int SEL_RPL_MASK ; 
 int /*<<< orphan*/  SETREG (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TSR_IRET ; 
 scalar_t__ TSR_JMP ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_PDPTE0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_PDPTE1 ; 
 int /*<<< orphan*/  VM_REG_GUEST_PDPTE2 ; 
 int /*<<< orphan*/  VM_REG_GUEST_PDPTE3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_RAX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RCX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int* paddr_guest2host (unsigned int,int) ; 
 int /*<<< orphan*/  update_seg_desc (int,int /*<<< orphan*/ ,struct seg_desc*) ; 
 int validate_seg_desc (int,struct vm_task_switch*,int /*<<< orphan*/ ,struct seg_desc*,int*) ; 
 int /*<<< orphan*/  vm_inject_gp (int) ; 
 int /*<<< orphan*/  xh_vm_copyout (struct tss32*,struct iovec*,int) ; 

__attribute__((used)) static int
tss32_restore(int vcpu, struct vm_task_switch *ts, uint16_t ot_sel,
	struct tss32 *tss, struct iovec *iov, int *faultptr)
{
	struct seg_desc seg_desc, seg_desc2;
	uint64_t *pdpte, maxphyaddr, reserved;
	uint32_t eflags;
	int error, i;
	bool nested;

	nested = false;
	if (ts->reason != TSR_IRET && ts->reason != TSR_JMP) {
		tss->tss_link = ot_sel;
		nested = true;
	}

	eflags = tss->tss_eflags;
	if (nested)
		eflags |= PSL_NT;

	/* LDTR */
	SETREG(vcpu, VM_REG_GUEST_LDTR, tss->tss_ldt);

	/* PBDR */
	if (ts->paging.paging_mode != PAGING_MODE_FLAT) {
		if (ts->paging.paging_mode == PAGING_MODE_PAE) {
			/*
			 * XXX Assuming 36-bit MAXPHYADDR.
			 */
			maxphyaddr = (1UL << 36) - 1;
			pdpte = paddr_guest2host(tss->tss_cr3 & ~((unsigned) 0x1f), 32);
			for (i = 0; i < 4; i++) {
				/* Check reserved bits if the PDPTE is valid */
				if (!(pdpte[i] & 0x1))
					continue;
				/*
				 * Bits 2:1, 8:5 and bits above the processor's
				 * maximum physical address are reserved.
				 */
				reserved = ~maxphyaddr | 0x1E6;
				if (pdpte[i] & reserved) {
					vm_inject_gp(vcpu);
					return (1);
				}
			}
			SETREG(vcpu, VM_REG_GUEST_PDPTE0, pdpte[0]);
			SETREG(vcpu, VM_REG_GUEST_PDPTE1, pdpte[1]);
			SETREG(vcpu, VM_REG_GUEST_PDPTE2, pdpte[2]);
			SETREG(vcpu, VM_REG_GUEST_PDPTE3, pdpte[3]);
		}
		SETREG(vcpu, VM_REG_GUEST_CR3, tss->tss_cr3);
		ts->paging.cr3 = tss->tss_cr3;
	}

	/* eflags and eip */
	SETREG(vcpu, VM_REG_GUEST_RFLAGS, eflags);
	SETREG(vcpu, VM_REG_GUEST_RIP, tss->tss_eip);

	/* General purpose registers */
	SETREG(vcpu, VM_REG_GUEST_RAX, tss->tss_eax);
	SETREG(vcpu, VM_REG_GUEST_RCX, tss->tss_ecx);
	SETREG(vcpu, VM_REG_GUEST_RDX, tss->tss_edx);
	SETREG(vcpu, VM_REG_GUEST_RBX, tss->tss_ebx);
	SETREG(vcpu, VM_REG_GUEST_RSP, tss->tss_esp);
	SETREG(vcpu, VM_REG_GUEST_RBP, tss->tss_ebp);
	SETREG(vcpu, VM_REG_GUEST_RSI, tss->tss_esi);
	SETREG(vcpu, VM_REG_GUEST_RDI, tss->tss_edi);

	/* Segment selectors */
	SETREG(vcpu, VM_REG_GUEST_ES, tss->tss_es);
	SETREG(vcpu, VM_REG_GUEST_CS, tss->tss_cs);
	SETREG(vcpu, VM_REG_GUEST_SS, tss->tss_ss);
	SETREG(vcpu, VM_REG_GUEST_DS, tss->tss_ds);
	SETREG(vcpu, VM_REG_GUEST_FS, tss->tss_fs);
	SETREG(vcpu, VM_REG_GUEST_GS, tss->tss_gs);

	/*
	 * If this is a nested task then write out the new TSS to update
	 * the previous link field.
	 */
	if (nested)
		xh_vm_copyout(tss, iov, sizeof(*tss));

	/* Validate segment descriptors */
	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_LDTR, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_LDTR, &seg_desc);

	/*
	 * Section "Checks on Guest Segment Registers", Intel SDM, Vol 3.
	 *
	 * The SS and CS attribute checks on VM-entry are inter-dependent so
	 * we need to make sure that both segments are valid before updating
	 * either of them. This ensures that the VMCS state can pass the
	 * VM-entry checks so the guest can handle any exception injected
	 * during task switch emulation.
	 */
	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_CS, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);

	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_SS, &seg_desc2,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_CS, &seg_desc);
	update_seg_desc(vcpu, VM_REG_GUEST_SS, &seg_desc2);
	ts->paging.cpl = tss->tss_cs & SEL_RPL_MASK;

	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_DS, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_DS, &seg_desc);

	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_ES, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_ES, &seg_desc);

	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_FS, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_FS, &seg_desc);

	error = validate_seg_desc(vcpu, ts, VM_REG_GUEST_GS, &seg_desc,
	    faultptr);
	if (error || *faultptr)
		return (error);
	update_seg_desc(vcpu, VM_REG_GUEST_GS, &seg_desc);

	return (0);
}