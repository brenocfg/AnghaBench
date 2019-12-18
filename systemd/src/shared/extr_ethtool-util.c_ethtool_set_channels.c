#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifreq {void* ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; scalar_t__ other_count; scalar_t__ combined_count; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {scalar_t__ rx_count; scalar_t__ tx_count; scalar_t__ other_count; scalar_t__ combined_count; scalar_t__ combined_count_set; scalar_t__ other_count_set; scalar_t__ tx_count_set; scalar_t__ rx_count_set; } ;
typedef  TYPE_1__ netdev_channels ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_GCHANNELS ; 
 int /*<<< orphan*/  ETHTOOL_SCHANNELS ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCETHTOOL ; 
 int errno ; 
 int ethtool_connect_or_warn (int*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int ethtool_set_channels(int *fd, const char *ifname, netdev_channels *channels) {
        struct ethtool_channels ecmd = {
                .cmd = ETHTOOL_GCHANNELS
        };
        struct ifreq ifr = {
                .ifr_data = (void*) &ecmd
        };

        bool need_update = false;
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

        if (channels->rx_count_set && ecmd.rx_count != channels->rx_count) {
                ecmd.rx_count = channels->rx_count;
                need_update = true;
        }

        if (channels->tx_count_set && ecmd.tx_count != channels->tx_count) {
                ecmd.tx_count = channels->tx_count;
                need_update = true;
        }

        if (channels->other_count_set && ecmd.other_count != channels->other_count) {
                ecmd.other_count = channels->other_count;
                need_update = true;
        }

        if (channels->combined_count_set && ecmd.combined_count != channels->combined_count) {
                ecmd.combined_count = channels->combined_count;
                need_update = true;
        }

        if (need_update) {
                ecmd.cmd = ETHTOOL_SCHANNELS;

                r = ioctl(*fd, SIOCETHTOOL, &ifr);
                if (r < 0)
                        return -errno;
        }

        return 0;
}