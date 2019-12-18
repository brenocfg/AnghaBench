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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (unsigned int,int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int IOART_DELEXINT ; 
 int IOART_DELFIXED ; 
 int IOART_DELLOPRI ; 
 int /*<<< orphan*/  VM_CTR1 (struct vm*,char*,int) ; 
 int /*<<< orphan*/  lapic_set_intr (struct vm*,int,int,int) ; 
 int /*<<< orphan*/  vlapic_calcdest (struct vm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vm_inject_extint (struct vm*,int) ; 

void
vlapic_deliver_intr(struct vm *vm, bool level, uint32_t dest, bool phys,
    int delmode, int vec)
{
	bool lowprio;
	int vcpuid;
	cpuset_t dmask;

	if (delmode != IOART_DELFIXED &&
	    delmode != IOART_DELLOPRI &&
	    delmode != IOART_DELEXINT) {
		VM_CTR1(vm, "vlapic intr invalid delmode %#x", delmode);
		return;
	}
	lowprio = (delmode == IOART_DELLOPRI);

	/*
	 * We don't provide any virtual interrupt redirection hardware so
	 * all interrupts originating from the ioapic or MSI specify the
	 * 'dest' in the legacy xAPIC format.
	 */
	vlapic_calcdest(vm, &dmask, dest, phys, lowprio, false);

	while ((vcpuid = CPU_FFS(&dmask)) != 0) {
		vcpuid--;
		CPU_CLR(((unsigned) vcpuid), &dmask);
		if (delmode == IOART_DELEXINT) {
			vm_inject_extint(vm, vcpuid);
		} else {
			lapic_set_intr(vm, vcpuid, vec, level);
		}
	}
}