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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int vcpu; int rip; } ;
struct TYPE_4__ {TYPE_1__ spinup_ap; } ;
struct vm_exit {TYPE_2__ u; int /*<<< orphan*/  exitcode; } ;
struct vlapic {scalar_t__ vcpuid; scalar_t__ boot_state; int /*<<< orphan*/  vm; struct LAPIC* apic_page; } ;
struct LAPIC {unsigned int icr_lo; scalar_t__ icr_hi; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int APIC_DELMODE_FIXED ; 
 int APIC_DELMODE_INIT ; 
 int APIC_DELMODE_MASK ; 
 int APIC_DELMODE_NMI ; 
 int APIC_DELMODE_STARTUP ; 
 scalar_t__ APIC_DELSTAT_PEND ; 
 int APIC_DESTMODE_LOG ; 
#define  APIC_DEST_ALLESELF 131 
#define  APIC_DEST_ALLISELF 130 
#define  APIC_DEST_DESTFLD 129 
 int APIC_DEST_MASK ; 
#define  APIC_DEST_SELF 128 
 int /*<<< orphan*/  APIC_ESR_SEND_ILLEGAL_VECTOR ; 
 int APIC_LEVEL_DEASSERT ; 
 int APIC_LEVEL_MASK ; 
 int APIC_VECTOR_MASK ; 
 scalar_t__ BS_INIT ; 
 scalar_t__ BS_RUNNING ; 
 scalar_t__ BS_SIPI ; 
 int /*<<< orphan*/  CPU_CLR (unsigned int,int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETOF (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPIS_SENT ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int) ; 
 int /*<<< orphan*/  VLAPIC_CTR2 (struct vlapic*,char*,int,int) ; 
 int /*<<< orphan*/  VM_EXITCODE_SPINUP_AP ; 
 int VM_MAXCPU ; 
 int XHYVE_PAGE_SHIFT ; 
 int /*<<< orphan*/  lapic_intr_edge (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vlapic_calcdest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  vlapic_set_error (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_active_cpus (int /*<<< orphan*/ ) ; 
 struct vm_exit* vm_exitinfo (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_inject_nmi (int /*<<< orphan*/ ,int) ; 
 struct vlapic* vm_lapic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmm_stat_array_incr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ x2apic (struct vlapic*) ; 

int
vlapic_icrlo_write_handler(struct vlapic *vlapic, bool *retu)
{
	int i;
	bool phys;
	cpuset_t dmask;
	uint64_t icrval;
	uint32_t dest, vec, mode;
	struct vlapic *vlapic2;
	struct vm_exit *vmexit;
	struct LAPIC *lapic;

	lapic = vlapic->apic_page;
	lapic->icr_lo &= ~((unsigned) APIC_DELSTAT_PEND);
	icrval = ((uint64_t)lapic->icr_hi << 32) | lapic->icr_lo;

	if (x2apic(vlapic))
		dest = icrval >> 32;
	else
		dest = icrval >> (32 + 24);
	vec = icrval & APIC_VECTOR_MASK;
	mode = icrval & APIC_DELMODE_MASK;

	if (mode == APIC_DELMODE_FIXED && vec < 16) {
		vlapic_set_error(vlapic, APIC_ESR_SEND_ILLEGAL_VECTOR);
		VLAPIC_CTR1(vlapic, "Ignoring invalid IPI %d", vec);
		return (0);
	}

	VLAPIC_CTR2(vlapic, "icrlo 0x%016llx triggered ipi %d", icrval, vec);

	if (mode == APIC_DELMODE_FIXED || mode == APIC_DELMODE_NMI) {
		switch (icrval & APIC_DEST_MASK) {
		case APIC_DEST_DESTFLD:
			phys = ((icrval & APIC_DESTMODE_LOG) == 0);
			vlapic_calcdest(vlapic->vm, &dmask, dest, phys, false,
			    x2apic(vlapic));
			break;
		case APIC_DEST_SELF:
			CPU_SETOF(((unsigned) vlapic->vcpuid), &dmask);
			break;
		case APIC_DEST_ALLISELF:
			dmask = vm_active_cpus(vlapic->vm);
			break;
		case APIC_DEST_ALLESELF:
			dmask = vm_active_cpus(vlapic->vm);
			CPU_CLR(((unsigned) vlapic->vcpuid), &dmask);
			break;
		default:
			CPU_ZERO(&dmask);	/* satisfy gcc */
			break;
		}

		while ((i = CPU_FFS(&dmask)) != 0) {
			i--;
			CPU_CLR(((unsigned) i), &dmask);
			if (mode == APIC_DELMODE_FIXED) {
				lapic_intr_edge(vlapic->vm, i, ((int) vec));
				vmm_stat_array_incr(vlapic->vm, vlapic->vcpuid,
						    IPIS_SENT, i, 1);
				VLAPIC_CTR2(vlapic, "vlapic sending ipi %d "
				    "to vcpuid %d", vec, i);
			} else {
				vm_inject_nmi(vlapic->vm, i);
				VLAPIC_CTR1(vlapic, "vlapic sending ipi nmi "
				    "to vcpuid %d", i);
			}
		}

		return (0);	/* handled completely in the kernel */
	}

	if (mode == APIC_DELMODE_INIT) {
		if ((icrval & APIC_LEVEL_MASK) == APIC_LEVEL_DEASSERT)
			return (0);

		if (vlapic->vcpuid == 0 && dest != 0 && dest < VM_MAXCPU) {
			vlapic2 = vm_lapic(vlapic->vm, ((int) dest));

			/* move from INIT to waiting-for-SIPI state */
			if (vlapic2->boot_state == BS_INIT) {
				vlapic2->boot_state = BS_SIPI;
			}

			return (0);
		}
	}

	if (mode == APIC_DELMODE_STARTUP) {
		if (vlapic->vcpuid == 0 && dest != 0 && dest < VM_MAXCPU) {
			vlapic2 = vm_lapic(vlapic->vm, ((int) dest));

			/*
			 * Ignore SIPIs in any state other than wait-for-SIPI
			 */
			if (vlapic2->boot_state != BS_SIPI)
				return (0);

			vlapic2->boot_state = BS_RUNNING;

			*retu = true;
			vmexit = vm_exitinfo(vlapic->vm, vlapic->vcpuid);
			vmexit->exitcode = VM_EXITCODE_SPINUP_AP;
			vmexit->u.spinup_ap.vcpu = (int) dest;
			vmexit->u.spinup_ap.rip = vec << XHYVE_PAGE_SHIFT;

			return (0);
		}
	}

	/*
	 * This will cause a return to userland.
	 */
	return (1);
}