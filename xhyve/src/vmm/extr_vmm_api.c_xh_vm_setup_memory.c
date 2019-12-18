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
typedef  enum vm_mmap_style { ____Placeholder_vm_mmap_style } vm_mmap_style ;

/* Variables and functions */
 int VM_MMAP_ALL ; 
 int VM_MMAP_NONE ; 
 int XHYVE_PROT_EXECUTE ; 
 int XHYVE_PROT_READ ; 
 int XHYVE_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t highmem ; 
 void* highmem_addr ; 
 size_t lowmem ; 
 void* lowmem_addr ; 
 size_t lowmem_limit ; 
 int mmap_style ; 
 int setup_memory_segment (unsigned long long,size_t,int const,void**) ; 

int
xh_vm_setup_memory(size_t len, enum vm_mmap_style vms)
{
	void **addr;
	int error;
    const uint64_t protFlags = XHYVE_PROT_READ | XHYVE_PROT_WRITE | XHYVE_PROT_EXECUTE;

	/* XXX VM_MMAP_SPARSE not implemented yet */
	assert(vms == VM_MMAP_NONE || vms == VM_MMAP_ALL);

	mmap_style = vms;

	/*
	 * If 'len' cannot fit entirely in the 'lowmem' segment then
	 * create another 'highmem' segment above 4GB for the remainder.
	 */

	lowmem = (len > lowmem_limit) ? lowmem_limit : len;
	highmem = (len > lowmem_limit) ? (len - lowmem) : 0;

	if (lowmem > 0) {
		addr = (vms == VM_MMAP_ALL) ? &lowmem_addr : NULL;
		if ((error = setup_memory_segment(0, lowmem, protFlags, addr))) {
			return (error);
		}
	}

	if (highmem > 0) {
		addr = (vms == VM_MMAP_ALL) ? &highmem_addr : NULL;
		if ((error = setup_memory_segment((4ull << 30), highmem, protFlags, addr))) {
			return (error);
		}
	}

	return (0);
}