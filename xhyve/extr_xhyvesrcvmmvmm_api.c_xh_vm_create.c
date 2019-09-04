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

/* Variables and functions */
 int EEXIST ; 
 unsigned long long lowmem_limit ; 
 scalar_t__ memflags ; 
 int /*<<< orphan*/ * vm ; 
 int vm_create (int /*<<< orphan*/ **) ; 
 int vmm_init () ; 

int
xh_vm_create(void)
{
	int error;

	if (vm != NULL) {
		return (EEXIST);
	}

	error =	vmm_init();

	if (error != 0) {
		return (error);
	}

	memflags = 0;
	lowmem_limit = (3ull << 30);

	return (vm_create(&vm));
}