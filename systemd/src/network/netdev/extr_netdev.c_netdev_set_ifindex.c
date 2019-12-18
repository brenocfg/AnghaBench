#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_16__ {int ifindex; char const* ifname; scalar_t__ kind; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_INFO_KIND ; 
 int /*<<< orphan*/  IFLA_LINKINFO ; 
 scalar_t__ NETDEV_KIND_TAP ; 
 scalar_t__ RTM_NEWLINK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_netdev_debug (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  log_netdev_error (TYPE_1__*,char*,...) ; 
 int log_netdev_error_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  netdev_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_enter_ready (TYPE_1__*) ; 
 char* netdev_kind_to_string (scalar_t__) ; 
 int sd_netlink_message_enter_container (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_exit_container (TYPE_1__*) ; 
 int sd_netlink_message_get_type (TYPE_1__*,scalar_t__*) ; 
 int sd_netlink_message_read_string (TYPE_1__*,int /*<<< orphan*/ ,char const**) ; 
 int sd_rtnl_message_link_get_ifindex (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  streq (char const*,char const*) ; 

int netdev_set_ifindex(NetDev *netdev, sd_netlink_message *message) {
        uint16_t type;
        const char *kind;
        const char *received_kind;
        const char *received_name;
        int r, ifindex;

        assert(netdev);
        assert(message);

        r = sd_netlink_message_get_type(message, &type);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not get rtnl message type: %m");

        if (type != RTM_NEWLINK) {
                log_netdev_error(netdev, "Cannot set ifindex from unexpected rtnl message type.");
                return -EINVAL;
        }

        r = sd_rtnl_message_link_get_ifindex(message, &ifindex);
        if (r < 0) {
                log_netdev_error_errno(netdev, r, "Could not get ifindex: %m");
                netdev_enter_failed(netdev);
                return r;
        } else if (ifindex <= 0) {
                log_netdev_error(netdev, "Got invalid ifindex: %d", ifindex);
                netdev_enter_failed(netdev);
                return -EINVAL;
        }

        if (netdev->ifindex > 0) {
                if (netdev->ifindex != ifindex) {
                        log_netdev_error(netdev, "Could not set ifindex to %d, already set to %d",
                                         ifindex, netdev->ifindex);
                        netdev_enter_failed(netdev);
                        return -EEXIST;
                } else
                        /* ifindex already set to the same for this netdev */
                        return 0;
        }

        r = sd_netlink_message_read_string(message, IFLA_IFNAME, &received_name);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not get IFNAME: %m");

        if (!streq(netdev->ifname, received_name)) {
                log_netdev_error(netdev, "Received newlink with wrong IFNAME %s", received_name);
                netdev_enter_failed(netdev);
                return r;
        }

        r = sd_netlink_message_enter_container(message, IFLA_LINKINFO);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not get LINKINFO: %m");

        r = sd_netlink_message_read_string(message, IFLA_INFO_KIND, &received_kind);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not get KIND: %m");

        r = sd_netlink_message_exit_container(message);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not exit container: %m");

        if (netdev->kind == NETDEV_KIND_TAP)
                /* the kernel does not distinguish between tun and tap */
                kind = "tun";
        else {
                kind = netdev_kind_to_string(netdev->kind);
                if (!kind) {
                        log_netdev_error(netdev, "Could not get kind");
                        netdev_enter_failed(netdev);
                        return -EINVAL;
                }
        }

        if (!streq(kind, received_kind)) {
                log_netdev_error(netdev,
                                 "Received newlink with wrong KIND %s, "
                                 "expected %s", received_kind, kind);
                netdev_enter_failed(netdev);
                return r;
        }

        netdev->ifindex = ifindex;

        log_netdev_debug(netdev, "netdev has index %d", netdev->ifindex);

        netdev_enter_ready(netdev);

        return 0;
}