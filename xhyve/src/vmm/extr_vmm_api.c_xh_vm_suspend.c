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
typedef  enum vm_suspend_how { ____Placeholder_vm_suspend_how } vm_suspend_how ;

/* Variables and functions */
 int /*<<< orphan*/  vm ; 
 int vm_suspend (int /*<<< orphan*/ ,int) ; 

int
xh_vm_suspend(enum vm_suspend_how how)
{
	return (vm_suspend(vm, how));
}