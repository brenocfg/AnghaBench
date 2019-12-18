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
struct ethtool_cmd {int /*<<< orphan*/  cmd; int /*<<< orphan*/  duplex; } ;
typedef  int Duplex ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
#define  DUP_FULL 129 
#define  DUP_HALF 128 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  ETHTOOL_SSET ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCETHTOOL ; 
 int _DUP_INVALID ; 
 int errno ; 
 unsigned int ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,unsigned int) ; 
 int ethtool_connect_or_warn (int*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int ethtool_set_speed(int *fd, const char *ifname, unsigned speed, Duplex duplex) {
        struct ethtool_cmd ecmd = {
                .cmd = ETHTOOL_GSET
        };
        struct ifreq ifr = {
                .ifr_data = (void*) &ecmd
        };
        bool need_update = false;
        int r;

        if (speed == 0 && duplex == _DUP_INVALID)
                return 0;

        if (*fd < 0) {
                r = ethtool_connect_or_warn(fd, true);
                if (r < 0)
                        return r;
        }

        strscpy(ifr.ifr_name, IFNAMSIZ, ifname);

        r = ioctl(*fd, SIOCETHTOOL, &ifr);
        if (r < 0)
                return -errno;

        if (ethtool_cmd_speed(&ecmd) != speed) {
                ethtool_cmd_speed_set(&ecmd, speed);
                need_update = true;
        }

        switch (duplex) {
                case DUP_HALF:
                        if (ecmd.duplex != DUPLEX_HALF) {
                                ecmd.duplex = DUPLEX_HALF;
                                need_update = true;
                        }
                        break;
                case DUP_FULL:
                        if (ecmd.duplex != DUPLEX_FULL) {
                                ecmd.duplex = DUPLEX_FULL;
                                need_update = true;
                        }
                        break;
                default:
                        break;
        }

        if (need_update) {
                ecmd.cmd = ETHTOOL_SSET;

                r = ioctl(*fd, SIOCETHTOOL, &ifr);
                if (r < 0)
                        return -errno;
        }

        return 0;
}