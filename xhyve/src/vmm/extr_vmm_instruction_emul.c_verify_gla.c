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
struct vm {int dummy; } ;
struct vie {int base_register; int index_register; int scale; size_t addrsize; scalar_t__ displacement; scalar_t__ num_valid; } ;

/* Variables and functions */
 int VIE_INVALID_GLA ; 
 int VM_REG_GUEST_RIP ; 
 int VM_REG_LAST ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int* size2mask ; 
 int vm_get_register (struct vm*,int,int,int*) ; 

__attribute__((used)) static int
verify_gla(struct vm *vm, int cpuid, uint64_t gla, struct vie *vie)
{
	int error;
	uint64_t base, idx, gla2;

	/* Skip 'gla' verification */
	if (gla == VIE_INVALID_GLA)
		return (0);

	base = 0;
	if (vie->base_register != VM_REG_LAST) {
		error = vm_get_register(vm, cpuid, vie->base_register, &base);
		if (error) {
			printf("verify_gla: error %d getting base reg %d\n",
				error, vie->base_register);
			return (-1);
		}

		/*
		 * RIP-relative addressing starts from the following
		 * instruction
		 */
		if (vie->base_register == VM_REG_GUEST_RIP)
			base += vie->num_valid;
	}

	idx = 0;
	if (vie->index_register != VM_REG_LAST) {
		error = vm_get_register(vm, cpuid, vie->index_register, &idx);
		if (error) {
			printf("verify_gla: error %d getting index reg %d\n",
				error, vie->index_register);
			return (-1);
		}
	}

	/* XXX assuming that the base address of the segment is 0 */
	gla2 = base + vie->scale * idx + ((uint64_t) vie->displacement);
	gla2 &= size2mask[vie->addrsize];
	if (gla != gla2) {
		printf("verify_gla mismatch: "
		       "base(0x%0llx), scale(%d), index(0x%0llx), "
		       "disp(0x%0llx), gla(0x%0llx), gla2(0x%0llx)\n",
		       base, vie->scale, idx, vie->displacement, gla, gla2);
		return (-1);
	}

	return (0);
}