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

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze_all (int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_get_memobj (int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__*,void**) ; 
 int vm_malloc (int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__) ; 

__attribute__((used)) static int
setup_memory_segment(uint64_t gpa, size_t len, uint64_t prot, void **addr)
{
	void *object;
	uint64_t offset;
	int error;

	vcpu_freeze_all(true);
	error = vm_malloc(vm, gpa, len, prot);
	if (error == 0) {
		error = vm_get_memobj(vm, gpa, len, &offset, &object);
		if (error == 0) {
			*addr = (void *) (((uintptr_t) object) + offset);
		}
	}
	vcpu_freeze_all(false);
	return (error);
}