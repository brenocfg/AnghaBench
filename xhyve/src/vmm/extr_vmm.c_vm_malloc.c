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
typedef  size_t uint64_t ;
struct vm {size_t num_mem_segs; struct mem_seg* mem_segs; } ;
struct mem_seg {size_t gpa; size_t len; void* object; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t VM_MAX_MEMORY_SEGMENTS ; 
 size_t XHYVE_PAGE_MASK ; 
 scalar_t__ XHYVE_PAGE_SIZE ; 
 scalar_t__ vm_mem_allocated (struct vm*,size_t) ; 
 void* vmm_mem_alloc (size_t,size_t,size_t) ; 

int
vm_malloc(struct vm *vm, uint64_t gpa, size_t len, uint64_t prot)
{
	int available, allocated;
	struct mem_seg *seg;
	void *object;
	uint64_t g;

	if ((gpa & XHYVE_PAGE_MASK) || (len & XHYVE_PAGE_MASK) || len == 0)
		return (EINVAL);
	
	available = allocated = 0;
	g = gpa;
	while (g < gpa + len) {
		if (vm_mem_allocated(vm, g))
			allocated++;
		else
			available++;

		g += XHYVE_PAGE_SIZE;
	}

	/*
	 * If there are some allocated and some available pages in the address
	 * range then it is an error.
	 */
	if (allocated && available)
		return (EINVAL);

	/*
	 * If the entire address range being requested has already been
	 * allocated then there isn't anything more to do.
	 */
	if (allocated && available == 0)
		return (0);

	if (vm->num_mem_segs >= VM_MAX_MEMORY_SEGMENTS)
		return (E2BIG);

	seg = &vm->mem_segs[vm->num_mem_segs];

	if ((object = vmm_mem_alloc(gpa, len, prot)) == NULL)
		return (ENOMEM);

	seg->gpa = gpa;
	seg->len = len;
	seg->object = object;

	vm->num_mem_segs++;

	return (0);
}