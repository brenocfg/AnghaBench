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
typedef  scalar_t__ uint64_t ;
struct vm {int dummy; } ;

/* Variables and functions */
 scalar_t__ vm_get_memobj (struct vm*,scalar_t__,scalar_t__,scalar_t__*,void**) ; 

void *
vm_gpa2hva(struct vm *vm, uint64_t gpa, uint64_t len) {
	void *base;
	uint64_t offset;

	if (vm_get_memobj(vm, gpa, len, &offset, &base)) {
		return NULL;
	}

	return (void *) (((uintptr_t) base) + offset);
}