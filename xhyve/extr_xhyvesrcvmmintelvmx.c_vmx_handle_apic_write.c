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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx {int dummy; } ;
struct vlapic {scalar_t__ apic_page; } ;

/* Variables and functions */
#define  APIC_OFFSET_CMCI_LVT 142 
#define  APIC_OFFSET_DFR 141 
#define  APIC_OFFSET_ERROR_LVT 140 
#define  APIC_OFFSET_ESR 139 
#define  APIC_OFFSET_ICR_LOW 138 
#define  APIC_OFFSET_ID 137 
#define  APIC_OFFSET_LDR 136 
#define  APIC_OFFSET_LINT0_LVT 135 
#define  APIC_OFFSET_LINT1_LVT 134 
#define  APIC_OFFSET_PERF_LVT 133 
 int APIC_OFFSET_SELF_IPI ; 
#define  APIC_OFFSET_SVR 132 
#define  APIC_OFFSET_THERM_LVT 131 
#define  APIC_OFFSET_TIMER_DCR 130 
#define  APIC_OFFSET_TIMER_ICR 129 
#define  APIC_OFFSET_TIMER_LVT 128 
 int APIC_WRITE_OFFSET (int /*<<< orphan*/ ) ; 
 int HANDLED ; 
 int UNHANDLED ; 
 int /*<<< orphan*/  apic_access_virtualization (struct vmx*,int) ; 
 int /*<<< orphan*/  vlapic_dcr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_dfr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_esr_write_handler (struct vlapic*) ; 
 int vlapic_icrlo_write_handler (struct vlapic*,int*) ; 
 int /*<<< orphan*/  vlapic_icrtmr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_id_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_ldr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_lvt_write_handler (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlapic_self_ipi_handler (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlapic_svr_write_handler (struct vlapic*) ; 
 scalar_t__ x2apic_virtualization (struct vmx*,int) ; 

__attribute__((used)) static int
vmx_handle_apic_write(struct vmx *vmx, int vcpuid, struct vlapic *vlapic,
    uint64_t qual)
{
	int error, handled, offset;
	uint32_t *apic_regs, vector;
	bool retu;

	handled = HANDLED;
	offset = APIC_WRITE_OFFSET(qual);

	if (!apic_access_virtualization(vmx, vcpuid)) {
		/*
		 * In general there should not be any APIC write VM-exits
		 * unless APIC-access virtualization is enabled.
		 *
		 * However self-IPI virtualization can legitimately trigger
		 * an APIC-write VM-exit so treat it specially.
		 */
		if (x2apic_virtualization(vmx, vcpuid) &&
		    offset == APIC_OFFSET_SELF_IPI) {
			apic_regs = (uint32_t *)(vlapic->apic_page);
			vector = apic_regs[APIC_OFFSET_SELF_IPI / 4];
			vlapic_self_ipi_handler(vlapic, vector);
			return (HANDLED);
		} else
			return (UNHANDLED);
	}

	switch (offset) {
	case APIC_OFFSET_ID:
		vlapic_id_write_handler(vlapic);
		break;
	case APIC_OFFSET_LDR:
		vlapic_ldr_write_handler(vlapic);
		break;
	case APIC_OFFSET_DFR:
		vlapic_dfr_write_handler(vlapic);
		break;
	case APIC_OFFSET_SVR:
		vlapic_svr_write_handler(vlapic);
		break;
	case APIC_OFFSET_ESR:
		vlapic_esr_write_handler(vlapic);
		break;
	case APIC_OFFSET_ICR_LOW:
		retu = false;
		error = vlapic_icrlo_write_handler(vlapic, &retu);
		if (error != 0 || retu)
			handled = UNHANDLED;
		break;
	case APIC_OFFSET_CMCI_LVT:
	case APIC_OFFSET_TIMER_LVT:
	case APIC_OFFSET_THERM_LVT:
	case APIC_OFFSET_PERF_LVT:
	case APIC_OFFSET_LINT0_LVT:
	case APIC_OFFSET_LINT1_LVT:
	case APIC_OFFSET_ERROR_LVT:
		vlapic_lvt_write_handler(vlapic, ((uint32_t) offset));
		break;
	case APIC_OFFSET_TIMER_ICR:
		vlapic_icrtmr_write_handler(vlapic);
		break;
	case APIC_OFFSET_TIMER_DCR:
		vlapic_dcr_write_handler(vlapic);
		break;
	default:
		handled = UNHANDLED;
		break;
	}
	return (handled);
}