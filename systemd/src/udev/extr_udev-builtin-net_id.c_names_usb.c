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
struct netnames {char* usb_ports; int /*<<< orphan*/  type; } ;
typedef  struct netnames sd_device ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  NET_USB ; 
 int /*<<< orphan*/  assert (struct netnames*) ; 
 int sd_device_get_parent_with_subsystem_devtype (struct netnames*,char*,char*,struct netnames**) ; 
 int sd_device_get_sysname (struct netnames*,char const**) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  streq (char*,char*) ; 
 size_t strpcpyl (char**,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (char*,int,char const*) ; 

__attribute__((used)) static int names_usb(sd_device *dev, struct netnames *names) {
        sd_device *usbdev;
        char name[256], *ports, *config, *interf, *s;
        const char *sysname;
        size_t l;
        int r;

        assert(dev);
        assert(names);

        r = sd_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_interface", &usbdev);
        if (r < 0)
                return r;

        r = sd_device_get_sysname(usbdev, &sysname);
        if (r < 0)
                return r;

        /* get USB port number chain, configuration, interface */
        strscpy(name, sizeof(name), sysname);
        s = strchr(name, '-');
        if (!s)
                return -EINVAL;
        ports = s+1;

        s = strchr(ports, ':');
        if (!s)
                return -EINVAL;
        s[0] = '\0';
        config = s+1;

        s = strchr(config, '.');
        if (!s)
                return -EINVAL;
        s[0] = '\0';
        interf = s+1;

        /* prefix every port number in the chain with "u" */
        s = ports;
        while ((s = strchr(s, '.')))
                s[0] = 'u';
        s = names->usb_ports;
        l = strpcpyl(&s, sizeof(names->usb_ports), "u", ports, NULL);

        /* append USB config number, suppress the common config == 1 */
        if (!streq(config, "1"))
                l = strpcpyl(&s, sizeof(names->usb_ports), "c", config, NULL);

        /* append USB interface number, suppress the interface == 0 */
        if (!streq(interf, "0"))
                l = strpcpyl(&s, sizeof(names->usb_ports), "i", interf, NULL);
        if (l == 0)
                return -ENAMETOOLONG;

        names->type = NET_USB;
        return 0;
}