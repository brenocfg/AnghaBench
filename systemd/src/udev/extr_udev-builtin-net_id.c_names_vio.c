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
struct netnames {int /*<<< orphan*/  type; int /*<<< orphan*/  vio_slot; } ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NET_VIO ; 
 int sd_device_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  streq (char*,char const*) ; 
 int /*<<< orphan*/  xsprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int names_vio(sd_device *dev, struct netnames *names) {
        sd_device *parent;
        unsigned busid, slotid, ethid;
        const char *syspath, *subsystem;
        int r;

        /* check if our direct parent is a VIO device with no other bus in-between */
        r = sd_device_get_parent(dev, &parent);
        if (r < 0)
                return r;

        r = sd_device_get_subsystem(parent, &subsystem);
        if (r < 0)
                return r;
        if (!streq("vio", subsystem))
                return -ENOENT;

        /* The devices' $DEVPATH number is tied to (virtual) hardware (slot id
         * selected in the HMC), thus this provides a reliable naming (e.g.
         * "/devices/vio/30000002/net/eth1"); we ignore the bus number, as
         * there should only ever be one bus, and then remove leading zeros. */
        r = sd_device_get_syspath(dev, &syspath);
        if (r < 0)
                return r;

        if (sscanf(syspath, "/sys/devices/vio/%4x%4x/net/eth%u", &busid, &slotid, &ethid) != 3)
                return -EINVAL;

        xsprintf(names->vio_slot, "v%u", slotid);
        names->type = NET_VIO;
        return 0;
}