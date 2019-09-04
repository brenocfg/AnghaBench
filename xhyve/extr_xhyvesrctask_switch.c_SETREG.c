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
 int /*<<< orphan*/  assert (int) ; 
 int xh_vm_set_register (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SETREG(int vcpu, int reg, uint64_t val)
{
	int error;

	error = xh_vm_set_register(vcpu, reg, val);
	assert(error == 0);
}