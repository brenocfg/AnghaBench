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
struct vm_memory_segment {scalar_t__ gpa; int /*<<< orphan*/  len; } ;
struct vm {int num_mem_segs; TYPE_1__* mem_segs; } ;
struct TYPE_2__ {scalar_t__ gpa; int /*<<< orphan*/  len; } ;

/* Variables and functions */

int
vm_gpabase2memseg(struct vm *vm, uint64_t gpabase,
		  struct vm_memory_segment *seg)
{
	int i;

	for (i = 0; i < vm->num_mem_segs; i++) {
		if (gpabase == vm->mem_segs[i].gpa) {
			seg->gpa = vm->mem_segs[i].gpa;
			seg->len = vm->mem_segs[i].len;
			return (0);
		}
	}
	return (-1);
}