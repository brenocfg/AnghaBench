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
typedef  int /*<<< orphan*/  hv_memory_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  HV_MEMORY_EXEC ; 
 int /*<<< orphan*/  HV_MEMORY_READ ; 
 int /*<<< orphan*/  HV_MEMORY_WRITE ; 
 int XHYVE_PROT_EXECUTE ; 
 int XHYVE_PROT_READ ; 
 int XHYVE_PROT_WRITE ; 
 scalar_t__ hv_vm_map (void*,int,size_t,int /*<<< orphan*/ ) ; 
 void* valloc (size_t) ; 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

void *
vmm_mem_alloc(uint64_t gpa, size_t size, uint64_t prot)
{
	void *object;
    hv_memory_flags_t hvProt;

	object = valloc(size);

	if (!object) {
		xhyve_abort("vmm_mem_alloc failed\n");
	}

    hvProt = (prot & XHYVE_PROT_READ) ? HV_MEMORY_READ : 0;
    hvProt |= (prot & XHYVE_PROT_WRITE) ? HV_MEMORY_WRITE : 0;
    hvProt |= (prot & XHYVE_PROT_EXECUTE) ? HV_MEMORY_EXEC : 0;

	if (hv_vm_map(object, gpa, size, hvProt))
	{
		xhyve_abort("hv_vm_map failed\n");
	}

	return object;
}