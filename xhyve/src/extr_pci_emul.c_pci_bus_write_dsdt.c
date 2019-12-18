#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct slotinfo {TYPE_1__* si_funcs; } ;
struct pci_devinst {TYPE_2__* pi_d; } ;
struct businfo {int iobase; int iolimit; int membase32; int memlimit32; int membase64; int memlimit64; struct slotinfo* slotinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pe_write_dsdt ) (struct pci_devinst*) ;} ;
struct TYPE_3__ {struct pci_devinst* fi_devi; } ;

/* Variables and functions */
 int MAXFUNCS ; 
 int MAXSLOTS ; 
 int PCI_EMUL_IOBASE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsdt_fixed_ioport (int,int) ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 int /*<<< orphan*/  dsdt_line (char*,...) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 
 int /*<<< orphan*/  pci_apic_prt_entry ; 
 struct businfo** pci_businfo ; 
 int pci_count_lintr (int) ; 
 int /*<<< orphan*/  pci_pirq_prt_entry ; 
 int /*<<< orphan*/  pci_walk_lintr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pci_devinst*) ; 

__attribute__((used)) static void
pci_bus_write_dsdt(int bus)
{
	struct businfo *bi;
	struct slotinfo *si;
	struct pci_devinst *pi;
	int count, func, slot;

	/*
	 * If there are no devices on this 'bus' then just return.
	 */
	if ((bi = pci_businfo[bus]) == NULL) {
		/*
		 * Bus 0 is special because it decodes the I/O ports used
		 * for PCI config space access even if there are no devices
		 * on it.
		 */
		if (bus != 0)
			return;
	}

	dsdt_line("  Device (PC%02X)", bus);
	dsdt_line("  {");
	dsdt_line("    Name (_HID, EisaId (\"PNP0A03\"))");
	dsdt_line("    Name (_ADR, Zero)");

	dsdt_line("    Method (_BBN, 0, NotSerialized)");
	dsdt_line("    {");
	dsdt_line("        Return (0x%08X)", bus);
	dsdt_line("    }");
	dsdt_line("    Name (_CRS, ResourceTemplate ()");
	dsdt_line("    {");
	dsdt_line("      WordBusNumber (ResourceProducer, MinFixed, "
	    "MaxFixed, PosDecode,");
	dsdt_line("        0x0000,             // Granularity");
	dsdt_line("        0x%04X,             // Range Minimum", bus);
	dsdt_line("        0x%04X,             // Range Maximum", bus);
	dsdt_line("        0x0000,             // Translation Offset");
	dsdt_line("        0x0001,             // Length");
	dsdt_line("        ,, )");

	if (bus == 0) {
		dsdt_indent(3);
		dsdt_fixed_ioport(0xCF8, 8);
		dsdt_unindent(3);

		dsdt_line("      WordIO (ResourceProducer, MinFixed, MaxFixed, "
		    "PosDecode, EntireRange,");
		dsdt_line("        0x0000,             // Granularity");
		dsdt_line("        0x0000,             // Range Minimum");
		dsdt_line("        0x0CF7,             // Range Maximum");
		dsdt_line("        0x0000,             // Translation Offset");
		dsdt_line("        0x0CF8,             // Length");
		dsdt_line("        ,, , TypeStatic)");

		dsdt_line("      WordIO (ResourceProducer, MinFixed, MaxFixed, "
		    "PosDecode, EntireRange,");
		dsdt_line("        0x0000,             // Granularity");
		dsdt_line("        0x0D00,             // Range Minimum");
		dsdt_line("        0x%04X,             // Range Maximum",
		    PCI_EMUL_IOBASE - 1);
		dsdt_line("        0x0000,             // Translation Offset");
		dsdt_line("        0x%04X,             // Length",
		    PCI_EMUL_IOBASE - 0x0D00);
		dsdt_line("        ,, , TypeStatic)");

		if (bi == NULL) {
			dsdt_line("    })");
			goto done;
		}
	}
	assert(bi != NULL);

	/* i/o window */
	dsdt_line("      WordIO (ResourceProducer, MinFixed, MaxFixed, "
	    "PosDecode, EntireRange,");
	dsdt_line("        0x0000,             // Granularity");
	dsdt_line("        0x%04X,             // Range Minimum", bi->iobase);
	dsdt_line("        0x%04X,             // Range Maximum",
	    bi->iolimit - 1);
	dsdt_line("        0x0000,             // Translation Offset");
	dsdt_line("        0x%04X,             // Length",
	    bi->iolimit - bi->iobase);
	dsdt_line("        ,, , TypeStatic)");

	/* mmio window (32-bit) */
	dsdt_line("      DWordMemory (ResourceProducer, PosDecode, "
	    "MinFixed, MaxFixed, NonCacheable, ReadWrite,");
	dsdt_line("        0x00000000,         // Granularity");
	dsdt_line("        0x%08X,         // Range Minimum\n", bi->membase32);
	dsdt_line("        0x%08X,         // Range Maximum\n",
	    bi->memlimit32 - 1);
	dsdt_line("        0x00000000,         // Translation Offset");
	dsdt_line("        0x%08X,         // Length\n",
	    bi->memlimit32 - bi->membase32);
	dsdt_line("        ,, , AddressRangeMemory, TypeStatic)");

	/* mmio window (64-bit) */
	dsdt_line("      QWordMemory (ResourceProducer, PosDecode, "
	    "MinFixed, MaxFixed, NonCacheable, ReadWrite,");
	dsdt_line("        0x0000000000000000, // Granularity");
	dsdt_line("        0x%016lX, // Range Minimum\n", bi->membase64);
	dsdt_line("        0x%016lX, // Range Maximum\n",
	    bi->memlimit64 - 1);
	dsdt_line("        0x0000000000000000, // Translation Offset");
	dsdt_line("        0x%016lX, // Length\n",
	    bi->memlimit64 - bi->membase64);
	dsdt_line("        ,, , AddressRangeMemory, TypeStatic)");
	dsdt_line("    })");

	count = pci_count_lintr(bus);
	if (count != 0) {
		dsdt_indent(2);
		dsdt_line("Name (PPRT, Package ()");
		dsdt_line("{");
		pci_walk_lintr(bus, pci_pirq_prt_entry, NULL);
 		dsdt_line("})");
		dsdt_line("Name (APRT, Package ()");
		dsdt_line("{");
		pci_walk_lintr(bus, pci_apic_prt_entry, NULL);
 		dsdt_line("})");
		dsdt_line("Method (_PRT, 0, NotSerialized)");
		dsdt_line("{");
		dsdt_line("  If (PICM)");
		dsdt_line("  {");
		dsdt_line("    Return (APRT)");
		dsdt_line("  }");
		dsdt_line("  Else");
		dsdt_line("  {");
		dsdt_line("    Return (PPRT)");
		dsdt_line("  }");
		dsdt_line("}");
		dsdt_unindent(2);
	}

	dsdt_indent(2);
	for (slot = 0; slot < MAXSLOTS; slot++) {
		si = &bi->slotinfo[slot];
		for (func = 0; func < MAXFUNCS; func++) {
			pi = si->si_funcs[func].fi_devi;
			if (pi != NULL && pi->pi_d->pe_write_dsdt != NULL)
				pi->pi_d->pe_write_dsdt(pi);
		}
	}
	dsdt_unindent(2);
done:
	dsdt_line("  }");
}