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
struct ethtool_wolinfo {int /*<<< orphan*/  cmd; int /*<<< orphan*/  wolopts; } ;
typedef  int WakeOnLan ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_GWOL ; 
 int /*<<< orphan*/  ETHTOOL_SWOL ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCETHTOOL ; 
 int /*<<< orphan*/  WAKE_ARP ; 
 int /*<<< orphan*/  WAKE_BCAST ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int /*<<< orphan*/  WAKE_MAGICSECURE ; 
 int /*<<< orphan*/  WAKE_MCAST ; 
 int /*<<< orphan*/  WAKE_PHY ; 
 int /*<<< orphan*/  WAKE_UCAST ; 
#define  WOL_ARP 135 
#define  WOL_BCAST 134 
#define  WOL_MAGIC 133 
#define  WOL_MAGICSECURE 132 
#define  WOL_MCAST 131 
#define  WOL_OFF 130 
#define  WOL_PHY 129 
#define  WOL_UCAST 128 
 int _WOL_INVALID ; 
 int errno ; 
 int ethtool_connect_or_warn (int*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int ethtool_set_wol(int *fd, const char *ifname, WakeOnLan wol) {
        struct ethtool_wolinfo ecmd = {
                .cmd = ETHTOOL_GWOL
        };
        struct ifreq ifr = {
                .ifr_data = (void*) &ecmd
        };
        bool need_update = false;
        int r;

        if (wol == _WOL_INVALID)
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

        switch (wol) {
        case WOL_PHY:
                if (ecmd.wolopts != WAKE_PHY) {
                        ecmd.wolopts = WAKE_PHY;
                        need_update = true;
                }
                break;
        case WOL_UCAST:
                if (ecmd.wolopts != WAKE_UCAST) {
                        ecmd.wolopts = WAKE_UCAST;
                        need_update = true;
                }
                break;
        case WOL_MCAST:
                if (ecmd.wolopts != WAKE_MCAST) {
                        ecmd.wolopts = WAKE_MCAST;
                        need_update = true;
                }
                break;
        case WOL_BCAST:
                if (ecmd.wolopts != WAKE_BCAST) {
                        ecmd.wolopts = WAKE_BCAST;
                        need_update = true;
                }
                break;
        case WOL_ARP:
                if (ecmd.wolopts != WAKE_ARP) {
                        ecmd.wolopts = WAKE_ARP;
                        need_update = true;
                }
                break;
        case WOL_MAGIC:
                if (ecmd.wolopts != WAKE_MAGIC) {
                        ecmd.wolopts = WAKE_MAGIC;
                        need_update = true;
                }
                break;
        case WOL_MAGICSECURE:
                if (ecmd.wolopts != WAKE_MAGICSECURE) {
                        ecmd.wolopts = WAKE_MAGICSECURE;
                        need_update = true;
                }
                break;
        case WOL_OFF:
                if (ecmd.wolopts != 0) {
                        ecmd.wolopts = 0;
                        need_update = true;
                }
                break;
        default:
                break;
        }

        if (need_update) {
                ecmd.cmd = ETHTOOL_SWOL;

                r = ioctl(*fd, SIOCETHTOOL, &ifr);
                if (r < 0)
                        return -errno;
        }

        return 0;
}