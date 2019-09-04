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
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vm*) ; 
 int /*<<< orphan*/  vm_cleanup (struct vm*,int) ; 

void
vm_destroy(struct vm *vm)
{
	vm_cleanup(vm, true);
	free(vm);
}