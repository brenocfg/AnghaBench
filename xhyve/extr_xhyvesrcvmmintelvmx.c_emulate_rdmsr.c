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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vmx {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X86_RAX ; 
 int /*<<< orphan*/  HV_X86_RDX ; 
 scalar_t__ lapic_msr (int /*<<< orphan*/ ) ; 
 int lapic_rdmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  reg_write (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int vmx_rdmsr (struct vmx*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
emulate_rdmsr(struct vmx *vmx, int vcpuid, u_int num, bool *retu)
{
	uint64_t result;
	uint32_t eax, edx;
	int error;

	if (lapic_msr(num))
		error = lapic_rdmsr(vmx->vm, vcpuid, num, &result, retu);
	else
		error = vmx_rdmsr(vmx, vcpuid, num, &result);

	if (error == 0) {
		eax = (uint32_t) result;
		reg_write(vcpuid, HV_X86_RAX, eax);
		edx = (uint32_t) (result >> 32);
		reg_write(vcpuid, HV_X86_RDX, edx);
	}

	return (error);
}