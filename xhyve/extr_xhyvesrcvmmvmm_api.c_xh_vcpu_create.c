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
 int vcpu_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vm ; 

int
xh_vcpu_create(int vcpu)
{
	assert(vm != NULL);
	return (vcpu_create(vm, vcpu));
}