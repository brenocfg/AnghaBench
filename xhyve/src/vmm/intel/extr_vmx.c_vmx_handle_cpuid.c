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
typedef  scalar_t__ uint32_t ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X86_RAX ; 
 int /*<<< orphan*/  HV_X86_RBX ; 
 int /*<<< orphan*/  HV_X86_RCX ; 
 int /*<<< orphan*/  HV_X86_RDX ; 
 scalar_t__ reg_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int x86_emulate_cpuid (struct vm*,int,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
vmx_handle_cpuid(struct vm *vm, int vcpuid)
{
	uint32_t eax, ebx, ecx, edx;
	int error;
	
	eax = (uint32_t) reg_read(vcpuid, HV_X86_RAX);
	ebx = (uint32_t) reg_read(vcpuid, HV_X86_RBX);
	ecx = (uint32_t) reg_read(vcpuid, HV_X86_RCX);
	edx = (uint32_t) reg_read(vcpuid, HV_X86_RDX);

	error = x86_emulate_cpuid(vm, vcpuid, &eax, &ebx, &ecx, &edx);

	reg_write(vcpuid, HV_X86_RAX, eax);
	reg_write(vcpuid, HV_X86_RBX, ebx);
	reg_write(vcpuid, HV_X86_RCX, ecx);
	reg_write(vcpuid, HV_X86_RDX, edx);

	return (error);
}