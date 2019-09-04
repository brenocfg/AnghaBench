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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm ; 
 int /*<<< orphan*/  vm_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ vmm_cleanup () ; 

void
xh_vm_destroy(void)
{
	assert(vm != NULL);

	vm_destroy(vm);

	if (vmm_cleanup() == 0) {
		vm = NULL;
	}
}