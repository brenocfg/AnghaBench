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
struct vlapic {int dummy; } ;

/* Variables and functions */
 int DEFAULT_APIC_BASE ; 
 int EINVAL ; 
 int vlapic_write (struct vlapic*,int,int,int,void*) ; 
 struct vlapic* vm_lapic (void*,int) ; 

int
lapic_mmio_write(void *vm, int cpu, uint64_t gpa, uint64_t wval, int size,
		 void *arg)
{
	int error;
	uint64_t off;
	struct vlapic *vlapic;
//printf("lapic_mmio_write 0x%016llx 0x%016llx\n", gpa, wval);
	off = gpa - DEFAULT_APIC_BASE;

	/*
	 * Memory mapped local apic accesses must be 4 bytes wide and
	 * aligned on a 16-byte boundary.
	 */
	if (size != 4 || off & 0xf)
		return (EINVAL);

	vlapic = vm_lapic(vm, cpu);
	error = vlapic_write(vlapic, 1, off, wval, arg);
	return (error);
}