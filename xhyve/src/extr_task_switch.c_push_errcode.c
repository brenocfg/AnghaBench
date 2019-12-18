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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vm_guest_paging {int /*<<< orphan*/  cpl; int /*<<< orphan*/  cpu_mode; } ;
struct seg_desc {int /*<<< orphan*/  access; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ GETREG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDT_SS ; 
 int SDT_SYS386BSY ; 
 int SDT_SYS386TSS ; 
 scalar_t__ SEG_DESC_DEF32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETREG (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  XHYVE_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nitems (struct iovec*) ; 
 int /*<<< orphan*/  sel_exception (int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ vie_alignment_check (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ vie_calculate_gla (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct seg_desc*,scalar_t__,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vm_inject_ac (int,int) ; 
 int xh_vm_copy_setup (int,struct vm_guest_paging*,scalar_t__,size_t,int /*<<< orphan*/ ,struct iovec*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xh_vm_copyout (scalar_t__*,struct iovec*,size_t) ; 
 int xh_vm_get_desc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
push_errcode(int vcpu, struct vm_guest_paging *paging, int task_type,
	uint32_t errcode, int *faultptr)
{
	struct iovec iov[2];
	struct seg_desc seg_desc;
	int stacksize, bytes, error;
	uint64_t gla, cr0, rflags;
	uint32_t esp;
	uint16_t stacksel;

	*faultptr = 0;

	cr0 = GETREG(vcpu, VM_REG_GUEST_CR0);
	rflags = GETREG(vcpu, VM_REG_GUEST_RFLAGS);
	stacksel = (uint16_t) GETREG(vcpu, VM_REG_GUEST_SS);

	error = xh_vm_get_desc(vcpu, VM_REG_GUEST_SS, &seg_desc.base,
	    &seg_desc.limit, &seg_desc.access);
	assert(error == 0);

	/*
	 * Section "Error Code" in the Intel SDM vol 3: the error code is
	 * pushed on the stack as a doubleword or word (depending on the
	 * default interrupt, trap or task gate size).
	 */
	if (task_type == SDT_SYS386BSY || task_type == SDT_SYS386TSS)
		bytes = 4;
	else
		bytes = 2;

	/*
	 * PUSH instruction from Intel SDM vol 2: the 'B' flag in the
	 * stack-segment descriptor determines the size of the stack
	 * pointer outside of 64-bit mode.
	 */
	if (SEG_DESC_DEF32(seg_desc.access))
		stacksize = 4;
	else
		stacksize = 2;

	esp = (uint32_t) GETREG(vcpu, VM_REG_GUEST_RSP);
	esp -= (uint32_t) bytes;

	if (vie_calculate_gla(paging->cpu_mode, VM_REG_GUEST_SS, &seg_desc, esp,
		bytes, stacksize, XHYVE_PROT_WRITE, &gla))
	{
		sel_exception(vcpu, IDT_SS, stacksel, 1);
		*faultptr = 1;
		return (0);
	}

	if (vie_alignment_check(paging->cpl, bytes, cr0, rflags, gla)) {
		vm_inject_ac(vcpu, 1);
		*faultptr = 1;
		return (0);
	}

	error = xh_vm_copy_setup(vcpu, paging, gla, ((size_t) bytes),
		XHYVE_PROT_WRITE, iov, nitems(iov), faultptr);
	if (error || *faultptr)
		return (error);

	xh_vm_copyout(&errcode, iov, ((size_t) bytes));
	SETREG(vcpu, VM_REG_GUEST_RSP, esp);
	return (0);
}