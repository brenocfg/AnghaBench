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

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hv_vm_unmap (int /*<<< orphan*/ ,size_t) ; 

void
vmm_mem_free(uint64_t gpa, size_t size, void *object)
{
	hv_vm_unmap(gpa, size);
	free(object);
}