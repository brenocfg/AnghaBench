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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct vm {int dummy; } ;

/* Variables and functions */
 int APIC_DELMODE_MASK ; 
 int /*<<< orphan*/  LAPIC_TRIG_EDGE ; 
 int MSI_X86_ADDR_BASE ; 
 int MSI_X86_ADDR_LOG ; 
 int MSI_X86_ADDR_MASK ; 
 int MSI_X86_ADDR_RH ; 
 int /*<<< orphan*/  VM_CTR1 (struct vm*,char*,int) ; 
 int /*<<< orphan*/  VM_CTR2 (struct vm*,char*,int,int) ; 
 int /*<<< orphan*/  VM_CTR3 (struct vm*,char*,char*,int,int) ; 
 int /*<<< orphan*/  vlapic_deliver_intr (struct vm*,int /*<<< orphan*/ ,int,int,int,int) ; 

int
lapic_intr_msi(struct vm *vm, uint64_t addr, uint64_t msg)
{
	int delmode, vec;
	uint32_t dest;
	bool phys;

	VM_CTR2(vm, "lapic MSI addr: %#llx msg: %#llx", addr, msg);

	if ((addr & MSI_X86_ADDR_MASK) != MSI_X86_ADDR_BASE) {
		VM_CTR1(vm, "lapic MSI invalid addr %#llx", addr);
		return (-1);
	}

	/*
	 * Extract the x86-specific fields from the MSI addr/msg
	 * params according to the Intel Arch spec, Vol3 Ch 10.
	 *
	 * The PCI specification does not support level triggered
	 * MSI/MSI-X so ignore trigger level in 'msg'.
	 *
	 * The 'dest' is interpreted as a logical APIC ID if both
	 * the Redirection Hint and Destination Mode are '1' and
	 * physical otherwise.
	 */
	dest = (addr >> 12) & 0xff;
	phys = ((addr & (MSI_X86_ADDR_RH | MSI_X86_ADDR_LOG)) !=
	    (MSI_X86_ADDR_RH | MSI_X86_ADDR_LOG));
	delmode = msg & APIC_DELMODE_MASK;
	vec = msg & 0xff;

	VM_CTR3(vm, "lapic MSI %s dest %#x, vec %d",
	    phys ? "physical" : "logical", dest, vec);

	vlapic_deliver_intr(vm, LAPIC_TRIG_EDGE, dest, phys, delmode, vec);
	return (0);
}