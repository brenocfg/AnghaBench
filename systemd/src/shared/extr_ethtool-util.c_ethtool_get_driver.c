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
struct ifreq {void* ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETHTOOL_GDRVINFO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCETHTOOL ; 
 int errno ; 
 int ethtool_connect_or_warn (int*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int ethtool_get_driver(int *fd, const char *ifname, char **ret) {
        struct ethtool_drvinfo ecmd = {
                .cmd = ETHTOOL_GDRVINFO
        };
        struct ifreq ifr = {
                .ifr_data = (void*) &ecmd
        };
        char *d;
        int r;

        if (*fd < 0) {
                r = ethtool_connect_or_warn(fd, true);
                if (r < 0)
                        return r;
        }

        strscpy(ifr.ifr_name, IFNAMSIZ, ifname);

        r = ioctl(*fd, SIOCETHTOOL, &ifr);
        if (r < 0)
                return -errno;

        d = strdup(ecmd.driver);
        if (!d)
                return -ENOMEM;

        *ret = d;
        return 0;
}