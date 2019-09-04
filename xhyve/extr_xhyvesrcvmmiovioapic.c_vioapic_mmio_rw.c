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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vioapic {scalar_t__ ioregsel; } ;

/* Variables and functions */
 scalar_t__ IOREGSEL ; 
 scalar_t__ IOWIN ; 
 scalar_t__ VIOAPIC_BASE ; 
 int /*<<< orphan*/  VIOAPIC_LOCK (struct vioapic*) ; 
 int /*<<< orphan*/  VIOAPIC_UNLOCK (struct vioapic*) ; 
 scalar_t__ vioapic_read (struct vioapic*,int,scalar_t__) ; 
 int /*<<< orphan*/  vioapic_write (struct vioapic*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
vioapic_mmio_rw(struct vioapic *vioapic, int vcpuid, uint64_t gpa,
    uint64_t *data, int size, bool doread)
{
	uint64_t offset;

	offset = gpa - VIOAPIC_BASE;

	/*
	 * The IOAPIC specification allows 32-bit wide accesses to the
	 * IOREGSEL (offset 0) and IOWIN (offset 16) registers.
	 */
	if (size != 4 || (offset != IOREGSEL && offset != IOWIN)) {
		if (doread)
			*data = 0;
		return (0);
	}

	VIOAPIC_LOCK(vioapic);
	if (offset == IOREGSEL) {
		if (doread)
			*data = vioapic->ioregsel;
		else
			vioapic->ioregsel = (uint32_t) *data;
	} else {
		if (doread) {
			*data = vioapic_read(vioapic, vcpuid,
			    vioapic->ioregsel);
		} else {
			vioapic_write(vioapic, vcpuid, vioapic->ioregsel,
				((uint32_t) *data));
		}
	}
	VIOAPIC_UNLOCK(vioapic);

	return (0);
}