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
struct netnames {unsigned int* mac; int mac_valid; } ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
#define  ARPHRD_INFINIBAND 128 
 int EINVAL ; 
 int sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int names_mac(sd_device *dev, struct netnames *names) {
        const char *s;
        unsigned long i;
        unsigned a1, a2, a3, a4, a5, a6;
        int r;

        /* Some kinds of devices tend to have hardware addresses
         * that are impossible to use in an iface name.
         */
        r = sd_device_get_sysattr_value(dev, "type", &s);
        if (r < 0)
                return r;

        i = strtoul(s, NULL, 0);
        switch (i) {
        /* The persistent part of a hardware address of an InfiniBand NIC
         * is 8 bytes long. We cannot fit this much in an iface name.
         */
        case ARPHRD_INFINIBAND:
                return -EINVAL;
        default:
                break;
        }

        /* check for NET_ADDR_PERM, skip random MAC addresses */
        r = sd_device_get_sysattr_value(dev, "addr_assign_type", &s);
        if (r < 0)
                return r;
        i = strtoul(s, NULL, 0);
        if (i != 0)
                return 0;

        r = sd_device_get_sysattr_value(dev, "address", &s);
        if (r < 0)
                return r;
        if (sscanf(s, "%x:%x:%x:%x:%x:%x", &a1, &a2, &a3, &a4, &a5, &a6) != 6)
                return -EINVAL;

        /* skip empty MAC addresses */
        if (a1 + a2 + a3 + a4 + a5 + a6 == 0)
                return -EINVAL;

        names->mac[0] = a1;
        names->mac[1] = a2;
        names->mac[2] = a3;
        names->mac[3] = a4;
        names->mac[4] = a5;
        names->mac[5] = a6;
        names->mac_valid = true;
        return 0;
}