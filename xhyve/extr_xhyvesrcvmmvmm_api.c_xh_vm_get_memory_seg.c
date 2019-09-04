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
typedef  int /*<<< orphan*/  uint64_t ;
struct vm_memory_segment {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm ; 
 int vm_gpabase2memseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_memory_segment*) ; 

int
xh_vm_get_memory_seg(uint64_t gpa, size_t *ret_len)
{
	int error;

	struct vm_memory_segment seg;

	error = vm_gpabase2memseg(vm, gpa, &seg);

	if (error == 0) {
		*ret_len = seg.len;
	}

	return (error);
}