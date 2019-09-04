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
 int VMM_INIT () ; 
 int /*<<< orphan*/ * ops ; 
 int /*<<< orphan*/  vmm_host_state_init () ; 
 int vmm_initialized ; 
 int vmm_mem_init () ; 
 int /*<<< orphan*/  vmm_ops_intel ; 

int
vmm_init(void)
{
	int error;

	vmm_host_state_init();

	error = vmm_mem_init();
	if (error)
		return (error);
	
	ops = &vmm_ops_intel;

	error = VMM_INIT();

	if (error == 0)
		vmm_initialized = 1;

	return (error);
}