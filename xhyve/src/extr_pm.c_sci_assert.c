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
 int /*<<< orphan*/  SCI_INT ; 
 int sci_active ; 
 int /*<<< orphan*/  xh_vm_isa_assert_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sci_assert(void)
{
	if (sci_active)
		return;
	xh_vm_isa_assert_irq(SCI_INT, SCI_INT);
	sci_active = 1;
}