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
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct vm_task_switch {scalar_t__ reason; } ;
struct tss32 {unsigned int tss_eflags; void* tss_eip; void* tss_gs; void* tss_fs; void* tss_ds; void* tss_ss; void* tss_cs; void* tss_es; void* tss_edi; void* tss_esi; void* tss_ebp; void* tss_esp; void* tss_ebx; void* tss_edx; void* tss_ecx; void* tss_eax; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ GETREG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ PSL_NT ; 
 scalar_t__ TSR_IRET ; 
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RAX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RCX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  xh_vm_copyout (struct tss32*,struct iovec*,int) ; 

__attribute__((used)) static void
tss32_save(int vcpu, struct vm_task_switch *task_switch,
    uint32_t eip, struct tss32 *tss, struct iovec *iov)
{

	/* General purpose registers */
	tss->tss_eax = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RAX);
	tss->tss_ecx = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RCX);
	tss->tss_edx = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RDX);
	tss->tss_ebx = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RBX);
	tss->tss_esp = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RSP);
	tss->tss_ebp = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RBP);
	tss->tss_esi = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RSI);
	tss->tss_edi = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RDI);

	/* Segment selectors */
	tss->tss_es = (uint16_t) GETREG(vcpu, VM_REG_GUEST_ES);
	tss->tss_cs = (uint16_t) GETREG(vcpu, VM_REG_GUEST_CS);
	tss->tss_ss = (uint16_t) GETREG(vcpu, VM_REG_GUEST_SS);
	tss->tss_ds = (uint16_t) GETREG(vcpu, VM_REG_GUEST_DS);
	tss->tss_fs = (uint16_t) GETREG(vcpu, VM_REG_GUEST_FS);
	tss->tss_gs = (uint16_t) GETREG(vcpu, VM_REG_GUEST_GS);

	/* eflags and eip */
	tss->tss_eflags = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RFLAGS);
	if (task_switch->reason == TSR_IRET)
		tss->tss_eflags &= ~((unsigned) PSL_NT);
	tss->tss_eip = eip;

	/* Copy updated old TSS into guest memory */
	xh_vm_copyout(tss, iov, sizeof(struct tss32));
}