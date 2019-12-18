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
struct netnames {char* pci_onboard; char const* pci_onboard_label; int /*<<< orphan*/ * pcidev; } ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NAMING_ZERO_ACPI_INDEX ; 
 unsigned long ONBOARD_INDEX_MAX ; 
 int /*<<< orphan*/  naming_scheme_has (int /*<<< orphan*/ ) ; 
 int safe_atolu (char const*,unsigned long*) ; 
 int sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 size_t strpcpyf (char**,size_t,char*,...) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dev_pci_onboard(sd_device *dev, struct netnames *names) {
        unsigned long idx, dev_port = 0;
        const char *attr, *port_name = NULL;
        size_t l;
        char *s;
        int r;

        /* ACPI _DSM — device specific method for naming a PCI or PCI Express device */
        if (sd_device_get_sysattr_value(names->pcidev, "acpi_index", &attr) < 0) {
                /* SMBIOS type 41 — Onboard Devices Extended Information */
                r = sd_device_get_sysattr_value(names->pcidev, "index", &attr);
                if (r < 0)
                        return r;
        }

        r = safe_atolu(attr, &idx);
        if (r < 0)
                return r;
        if (idx == 0 && !naming_scheme_has(NAMING_ZERO_ACPI_INDEX))
                return -EINVAL;

        /* Some BIOSes report rubbish indexes that are excessively high (2^24-1 is an index VMware likes to
         * report for example). Let's define a cut-off where we don't consider the index reliable anymore. We
         * pick some arbitrary cut-off, which is somewhere beyond the realistic number of physical network
         * interface a system might have. Ideally the kernel would already filter his crap for us, but it
         * doesn't currently. */
        if (idx > ONBOARD_INDEX_MAX)
                return -ENOENT;

        /* kernel provided port index for multiple ports on a single PCI function */
        if (sd_device_get_sysattr_value(dev, "dev_port", &attr) >= 0)
                dev_port = strtoul(attr, NULL, 10);

        /* kernel provided front panel port name for multiple port PCI device */
        (void) sd_device_get_sysattr_value(dev, "phys_port_name", &port_name);

        s = names->pci_onboard;
        l = sizeof(names->pci_onboard);
        l = strpcpyf(&s, l, "o%lu", idx);
        if (port_name)
                l = strpcpyf(&s, l, "n%s", port_name);
        else if (dev_port > 0)
                l = strpcpyf(&s, l, "d%lu", dev_port);
        if (l == 0)
                names->pci_onboard[0] = '\0';

        if (sd_device_get_sysattr_value(names->pcidev, "label", &names->pci_onboard_label) < 0)
                names->pci_onboard_label = NULL;

        return 0;
}