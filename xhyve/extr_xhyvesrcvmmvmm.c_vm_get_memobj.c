#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct vm {int num_mem_segs; TYPE_1__* mem_segs; } ;
struct TYPE_2__ {scalar_t__ gpa; size_t len; void* object; } ;

/* Variables and functions */
 int EINVAL ; 

int
vm_get_memobj(struct vm *vm, uint64_t gpa, size_t len,
	      uint64_t *offset, void **object)
{
	int i;
	size_t seg_len;
	uint64_t seg_gpa;
	void *seg_obj;

	for (i = 0; i < vm->num_mem_segs; i++) {
		if ((seg_obj = vm->mem_segs[i].object) == NULL)
			continue;

		seg_gpa = vm->mem_segs[i].gpa;
		seg_len = vm->mem_segs[i].len;

		if ((gpa >= seg_gpa) && ((gpa + len) <= (seg_gpa + seg_len))) {
			*offset = gpa - seg_gpa;
			*object = seg_obj;
			return (0);
		}
	}

	return (EINVAL);
}