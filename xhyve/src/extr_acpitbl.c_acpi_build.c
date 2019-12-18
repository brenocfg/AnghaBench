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
 int EFAULT ; 
 int /*<<< orphan*/  XHYVE_ACPI_BASE ; 
 int /*<<< orphan*/  XHYVE_ACPI_SIZE ; 
 int acpi_ncpu ; 
 int /*<<< orphan*/  acpitbl_build_dsdt () ; 
 int /*<<< orphan*/  acpitbl_build_facs () ; 
 int /*<<< orphan*/  acpitbl_build_fadt () ; 
 int /*<<< orphan*/  acpitbl_build_hpet () ; 
 int /*<<< orphan*/  acpitbl_build_madt () ; 
 int /*<<< orphan*/  acpitbl_build_mcfg () ; 
 int /*<<< orphan*/  acpitbl_build_rdsp () ; 
 int /*<<< orphan*/  acpitbl_build_rsdt () ; 
 int /*<<< orphan*/  acpitbl_build_xsdt () ; 
 int /*<<< orphan*/  hpet_capabilities ; 
 int /*<<< orphan*/ * paddr_guest2host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tb ; 
 int xh_vm_get_hpet_capabilities (int /*<<< orphan*/ *) ; 

int
acpi_build(int ncpu)
{
	int err;

	acpi_ncpu = ncpu;
	tb = paddr_guest2host(XHYVE_ACPI_BASE, XHYVE_ACPI_SIZE);
	if (tb == NULL) {
		return (EFAULT);
	}

	err = xh_vm_get_hpet_capabilities(&hpet_capabilities);
	if (err != 0) {
		return (err);
	}

	acpitbl_build_rdsp();
	acpitbl_build_rsdt();
	acpitbl_build_xsdt();
	acpitbl_build_madt();
	acpitbl_build_fadt();
	acpitbl_build_hpet();
	acpitbl_build_mcfg();
	acpitbl_build_facs();
	acpitbl_build_dsdt();

	return 0;
}