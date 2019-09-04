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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSP ; 
 int CR0_NE ; 
 int CR0_PE ; 
 int CR0_PG ; 
 int CR4_PAE ; 
 int DESC_UNUSABLE ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUEST_CODE_SEL ; 
 int /*<<< orphan*/  GUEST_DATA_SEL ; 
 int GUEST_GDTR_LIMIT64 ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR4 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_EFER ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  VM_REG_GUEST_TR ; 
 int xh_vm_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int xh_vm_set_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fbsd_set_regs(uint64_t rip, uint64_t cr3, uint64_t gdt_base, uint64_t rsp)
{
	int error;
	uint64_t cr0, cr4, efer, rflags, desc_base;
	uint32_t desc_access, desc_limit;
	uint16_t gsel;

	cr0 = CR0_PE | CR0_PG | CR0_NE;
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_CR0, cr0)) != 0)
		goto done;

	cr4 = CR4_PAE;
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_CR4, cr4)) != 0)
		goto done;

	efer = EFER_LME | EFER_LMA;
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_EFER, efer)))
		goto done;

	rflags = 0x2;
	error = xh_vm_set_register(BSP, VM_REG_GUEST_RFLAGS, rflags);
	if (error)
		goto done;

	desc_base = 0;
	desc_limit = 0;
	desc_access = 0x0000209B;
	error = xh_vm_set_desc(BSP, VM_REG_GUEST_CS, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	desc_access = 0x00000093;
	error = xh_vm_set_desc(BSP, VM_REG_GUEST_DS, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	error = xh_vm_set_desc(BSP, VM_REG_GUEST_ES, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	error = xh_vm_set_desc(BSP, VM_REG_GUEST_FS, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	error = xh_vm_set_desc(BSP, VM_REG_GUEST_GS, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	error = xh_vm_set_desc(BSP, VM_REG_GUEST_SS, desc_base, desc_limit,
		desc_access);

	if (error)
		goto done;

	/*
	 * XXX TR is pointing to null selector even though we set the
	 * TSS segment to be usable with a base address and limit of 0.
	 */
	desc_access = 0x0000008b;
	error = xh_vm_set_desc(BSP, VM_REG_GUEST_TR, 0, 0, desc_access);
	if (error)
		goto done;

	error = xh_vm_set_desc(BSP, VM_REG_GUEST_LDTR, 0, 0, DESC_UNUSABLE);
	if (error)
		goto done;

	gsel = GSEL(GUEST_CODE_SEL, SEL_KPL);
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_CS, gsel)) != 0)
		goto done;
	
	gsel = GSEL(GUEST_DATA_SEL, SEL_KPL);
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_DS, gsel)) != 0)
		goto done;
	
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_ES, gsel)) != 0)
		goto done;

	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_FS, gsel)) != 0)
		goto done;
	
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_GS, gsel)) != 0)
		goto done;
	
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_SS, gsel)) != 0)
		goto done;

	/* XXX TR is pointing to the null selector */
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_TR, 0)) != 0)
		goto done;

	/* LDTR is pointing to the null selector */
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_LDTR, 0)) != 0)
		goto done;

	/* entry point */
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_RIP, rip)) != 0)
		goto done;

	/* page table base */
	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_CR3, cr3)) != 0)
		goto done;

	desc_base = gdt_base;
	desc_limit = GUEST_GDTR_LIMIT64;
	error = xh_vm_set_desc(BSP, VM_REG_GUEST_GDTR, desc_base, desc_limit, 0);
	if (error != 0)
		goto done;

	if ((error = xh_vm_set_register(BSP, VM_REG_GUEST_RSP, rsp)) != 0)
		goto done;

	error = 0;
done:
	return (error);
}