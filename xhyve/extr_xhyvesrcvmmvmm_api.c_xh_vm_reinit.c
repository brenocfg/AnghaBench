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
 int /*<<< orphan*/  vcpu_freeze_all (int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_reinit (int /*<<< orphan*/ ) ; 

int
xh_vm_reinit(void)
{
	int error;

	vcpu_freeze_all(true);
	error = vm_reinit(vm);
	vcpu_freeze_all(false);

	return (error);
}