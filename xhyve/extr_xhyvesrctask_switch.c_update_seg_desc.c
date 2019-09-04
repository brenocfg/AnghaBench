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
struct seg_desc {int /*<<< orphan*/  access; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int xh_vm_set_desc (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_seg_desc(int vcpu, int reg, struct seg_desc *sd)
{
	int error;

	error = xh_vm_set_desc(vcpu, reg, sd->base, sd->limit, sd->access);
	assert(error == 0);
}