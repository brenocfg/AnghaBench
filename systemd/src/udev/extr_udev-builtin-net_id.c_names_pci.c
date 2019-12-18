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
struct virtfn_info {struct netnames* physfn_pcidev; scalar_t__* suffix; } ;
struct netnames {scalar_t__* pci_path; scalar_t__* pci_slot; scalar_t__* pci_onboard; struct netnames* pcidev; int /*<<< orphan*/  type; } ;
typedef  struct netnames sd_device ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NAMING_SR_IOV_V ; 
 int /*<<< orphan*/  NET_PCI ; 
 int /*<<< orphan*/  assert (struct netnames*) ; 
 int /*<<< orphan*/  dev_pci_onboard (struct netnames*,struct netnames*) ; 
 int /*<<< orphan*/  dev_pci_slot (struct netnames*,struct netnames*) ; 
 scalar_t__ get_virtfn_info (struct netnames*,struct netnames*,struct virtfn_info*) ; 
 scalar_t__ naming_scheme_has (int /*<<< orphan*/ ) ; 
 int sd_device_get_parent (struct netnames*,struct netnames**) ; 
 int sd_device_get_parent_with_subsystem_devtype (struct netnames*,char*,int /*<<< orphan*/ *,struct netnames**) ; 
 scalar_t__ sd_device_get_subsystem (struct netnames*,char const**) ; 
 int /*<<< orphan*/  sd_device_unref (struct netnames*) ; 
 struct netnames* skip_virtio (struct netnames*) ; 
 scalar_t__ streq (char*,char const*) ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strscpyl (scalar_t__*,int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int names_pci(sd_device *dev, struct netnames *names) {
        sd_device *parent;
        struct netnames vf_names = {};
        struct virtfn_info vf_info = {};
        const char *subsystem;
        int r;

        assert(dev);
        assert(names);

        r = sd_device_get_parent(dev, &parent);
        if (r < 0)
                return r;
        /* skip virtio subsystem if present */
        parent = skip_virtio(parent);

        if (!parent)
                return -ENOENT;

        /* check if our direct parent is a PCI device with no other bus in-between */
        if (sd_device_get_subsystem(parent, &subsystem) >= 0 &&
            streq("pci", subsystem)) {
                names->type = NET_PCI;
                names->pcidev = parent;
        } else {
                r = sd_device_get_parent_with_subsystem_devtype(dev, "pci", NULL, &names->pcidev);
                if (r < 0)
                        return r;
        }

        if (naming_scheme_has(NAMING_SR_IOV_V) &&
            get_virtfn_info(dev, names, &vf_info) >= 0) {
                /* If this is an SR-IOV virtual device, get base name using physical device and add virtfn suffix. */
                vf_names.pcidev = vf_info.physfn_pcidev;
                dev_pci_onboard(dev, &vf_names);
                dev_pci_slot(dev, &vf_names);
                if (vf_names.pci_onboard[0])
                        if (strlen(vf_names.pci_onboard) + strlen(vf_info.suffix) < sizeof(names->pci_onboard))
                                strscpyl(names->pci_onboard, sizeof(names->pci_onboard),
                                         vf_names.pci_onboard, vf_info.suffix, NULL);
                if (vf_names.pci_slot[0])
                        if (strlen(vf_names.pci_slot) + strlen(vf_info.suffix) < sizeof(names->pci_slot))
                                strscpyl(names->pci_slot, sizeof(names->pci_slot),
                                         vf_names.pci_slot, vf_info.suffix, NULL);
                if (vf_names.pci_path[0])
                        if (strlen(vf_names.pci_path) + strlen(vf_info.suffix) < sizeof(names->pci_path))
                                strscpyl(names->pci_path, sizeof(names->pci_path),
                                         vf_names.pci_path, vf_info.suffix, NULL);
                sd_device_unref(vf_info.physfn_pcidev);
        } else {
                dev_pci_onboard(dev, names);
                dev_pci_slot(dev, names);
        }

        return 0;
}