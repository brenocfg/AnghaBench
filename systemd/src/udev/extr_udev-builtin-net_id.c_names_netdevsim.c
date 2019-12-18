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
struct netnames {int /*<<< orphan*/  type; int /*<<< orphan*/  netdevsim_path; } ;
typedef  struct netnames sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NAMING_NETDEVSIM ; 
 int /*<<< orphan*/  NET_NETDEVSIM ; 
 int /*<<< orphan*/  assert (struct netnames*) ; 
 int /*<<< orphan*/  naming_scheme_has (int /*<<< orphan*/ ) ; 
 int sd_device_get_parent_with_subsystem_devtype (struct netnames*,char*,int /*<<< orphan*/ *,struct netnames**) ; 
 int sd_device_get_sysattr_value (struct netnames*,char*,char const**) ; 
 int sd_device_get_sysname (struct netnames*,char const**) ; 
 int snprintf_ok (int /*<<< orphan*/ ,int,char*,unsigned int,char const*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static int names_netdevsim(sd_device *dev, struct netnames *names) {
        sd_device *netdevsimdev;
        const char *sysname;
        unsigned addr;
        const char *port_name = NULL;
        int r;
        bool ok;

        if (!naming_scheme_has(NAMING_NETDEVSIM))
                return 0;

        assert(dev);
        assert(names);

        r = sd_device_get_parent_with_subsystem_devtype(dev, "netdevsim", NULL, &netdevsimdev);
        if (r < 0)
                return r;
        r = sd_device_get_sysname(netdevsimdev, &sysname);
        if (r < 0)
                return r;

        if (sscanf(sysname, "netdevsim%u", &addr) != 1)
                return -EINVAL;

        r = sd_device_get_sysattr_value(dev, "phys_port_name", &port_name);
        if (r < 0)
                return r;

        ok = snprintf_ok(names->netdevsim_path, sizeof(names->netdevsim_path), "i%un%s", addr, port_name);
        if (!ok)
                return -ENOBUFS;

        names->type = NET_NETDEVSIM;

        return 0;
}