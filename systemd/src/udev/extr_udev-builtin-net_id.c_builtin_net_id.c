#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netnames {scalar_t__ type; char* pci_path; char* pci_slot; int /*<<< orphan*/  bcma_core; int /*<<< orphan*/  usb_ports; scalar_t__ pci_onboard_label; scalar_t__* pci_onboard; int /*<<< orphan*/  netdevsim_path; int /*<<< orphan*/  platform_path; int /*<<< orphan*/  vio_slot; int /*<<< orphan*/  ccw_busid; int /*<<< orphan*/ * mac; scalar_t__ mac_valid; } ;
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
#define  ARPHRD_ETHER 130 
#define  ARPHRD_INFINIBAND 129 
#define  ARPHRD_SLIP 128 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NAMING_INFINIBAND ; 
 int /*<<< orphan*/  NAMING_LABEL_NOPREFIX ; 
 scalar_t__ NET_BCMA ; 
 scalar_t__ NET_CCW ; 
 scalar_t__ NET_NETDEVSIM ; 
 scalar_t__ NET_PCI ; 
 scalar_t__ NET_PLATFORM ; 
 scalar_t__ NET_USB ; 
 scalar_t__ NET_VIO ; 
 int /*<<< orphan*/  ieee_oui (int /*<<< orphan*/ *,struct netnames*,int) ; 
 scalar_t__ names_bcma (int /*<<< orphan*/ *,struct netnames*) ; 
 scalar_t__ names_ccw (int /*<<< orphan*/ *,struct netnames*) ; 
 int names_mac (int /*<<< orphan*/ *,struct netnames*) ; 
 scalar_t__ names_netdevsim (int /*<<< orphan*/ *,struct netnames*) ; 
 scalar_t__ names_pci (int /*<<< orphan*/ *,struct netnames*) ; 
 scalar_t__ names_platform (int /*<<< orphan*/ *,struct netnames*,int) ; 
 scalar_t__ names_usb (int /*<<< orphan*/ *,struct netnames*) ; 
 scalar_t__ names_vio (int /*<<< orphan*/ *,struct netnames*) ; 
 TYPE_1__* naming_scheme () ; 
 scalar_t__ naming_scheme_has (int /*<<< orphan*/ ) ; 
 scalar_t__ sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ snprintf (char*,int,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf_ok (char*,int,char*,char const*,char*,...) ; 
 scalar_t__ streq (char const*,char const*) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_builtin_add_property (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  xsprintf (char*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int builtin_net_id(sd_device *dev, int argc, char *argv[], bool test) {
        const char *s, *p, *devtype, *prefix = "en";
        struct netnames names = {};
        unsigned long i;
        int r;

        /* handle only ARPHRD_ETHER, ARPHRD_SLIP and ARPHRD_INFINIBAND devices */
        r = sd_device_get_sysattr_value(dev, "type", &s);
        if (r < 0)
                return r;

        i = strtoul(s, NULL, 0);
        switch (i) {
        case ARPHRD_ETHER:
                prefix = "en";
                break;
        case ARPHRD_INFINIBAND:
                if (naming_scheme_has(NAMING_INFINIBAND))
                        prefix = "ib";
                else
                        return 0;
                break;
        case ARPHRD_SLIP:
                prefix = "sl";
                break;
        default:
                return 0;
        }

        /* skip stacked devices, like VLANs, ... */
        r = sd_device_get_sysattr_value(dev, "ifindex", &s);
        if (r < 0)
                return r;
        r = sd_device_get_sysattr_value(dev, "iflink", &p);
        if (r < 0)
                return r;
        if (!streq(s, p))
                return 0;

        if (sd_device_get_devtype(dev, &devtype) >= 0) {
                if (streq("wlan", devtype))
                        prefix = "wl";
                else if (streq("wwan", devtype))
                        prefix = "ww";
        }

        udev_builtin_add_property(dev, test, "ID_NET_NAMING_SCHEME", naming_scheme()->name);

        r = names_mac(dev, &names);
        if (r >= 0 && names.mac_valid) {
                char str[IFNAMSIZ];

                xsprintf(str, "%sx%02x%02x%02x%02x%02x%02x", prefix,
                         names.mac[0], names.mac[1], names.mac[2],
                         names.mac[3], names.mac[4], names.mac[5]);
                udev_builtin_add_property(dev, test, "ID_NET_NAME_MAC", str);

                ieee_oui(dev, &names, test);
        }

        /* get path names for Linux on System z network devices */
        if (names_ccw(dev, &names) >= 0 && names.type == NET_CCW) {
                char str[IFNAMSIZ];

                if (snprintf_ok(str, sizeof str, "%s%s", prefix, names.ccw_busid))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);
                return 0;
        }

        /* get ibmveth/ibmvnic slot-based names. */
        if (names_vio(dev, &names) >= 0 && names.type == NET_VIO) {
                char str[IFNAMSIZ];

                if (snprintf_ok(str, sizeof str, "%s%s", prefix, names.vio_slot))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_SLOT", str);
                return 0;
        }

        /* get ACPI path names for ARM64 platform devices */
        if (names_platform(dev, &names, test) >= 0 && names.type == NET_PLATFORM) {
                char str[IFNAMSIZ];

                if (snprintf_ok(str, sizeof str, "%s%s", prefix, names.platform_path))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);
                return 0;
        }

        /* get netdevsim path names */
        if (names_netdevsim(dev, &names) >= 0 && names.type == NET_NETDEVSIM) {
                char str[IFNAMSIZ];

                if (snprintf_ok(str, sizeof str, "%s%s", prefix, names.netdevsim_path))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);

                return 0;
        }

        /* get PCI based path names, we compose only PCI based paths */
        if (names_pci(dev, &names) < 0)
                return 0;

        /* plain PCI device */
        if (names.type == NET_PCI) {
                char str[IFNAMSIZ];

                if (names.pci_onboard[0] &&
                    snprintf_ok(str, sizeof str, "%s%s", prefix, names.pci_onboard))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_ONBOARD", str);

                if (names.pci_onboard_label &&
                    snprintf_ok(str, sizeof str, "%s%s",
                                naming_scheme_has(NAMING_LABEL_NOPREFIX) ? "" : prefix,
                                names.pci_onboard_label))
                        udev_builtin_add_property(dev, test, "ID_NET_LABEL_ONBOARD", str);

                if (names.pci_path[0] &&
                    snprintf_ok(str, sizeof str, "%s%s", prefix, names.pci_path))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);

                if (names.pci_slot[0] &&
                    snprintf_ok(str, sizeof str, "%s%s", prefix, names.pci_slot))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_SLOT", str);
                return 0;
        }

        /* USB device */
        if (names_usb(dev, &names) >= 0 && names.type == NET_USB) {
                char str[IFNAMSIZ];

                if (names.pci_path[0] &&
                    snprintf_ok(str, sizeof str, "%s%s%s", prefix, names.pci_path, names.usb_ports))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);

                if (names.pci_slot[0] &&
                    snprintf_ok(str, sizeof str, "%s%s%s", prefix, names.pci_slot, names.usb_ports))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_SLOT", str);
                return 0;
        }

        /* Broadcom bus */
        if (names_bcma(dev, &names) >= 0 && names.type == NET_BCMA) {
                char str[IFNAMSIZ];

                if (names.pci_path[0] &&
                    snprintf_ok(str, sizeof str, "%s%s%s", prefix, names.pci_path, names.bcma_core))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_PATH", str);

                if (names.pci_slot[0] &&
                    snprintf(str, sizeof str, "%s%s%s", prefix, names.pci_slot, names.bcma_core))
                        udev_builtin_add_property(dev, test, "ID_NET_NAME_SLOT", str);
                return 0;
        }

        return 0;
}