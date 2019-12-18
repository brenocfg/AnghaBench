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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
typedef  int /*<<< orphan*/  NetDev ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IN_SET (int,int,int) ; 
#define  RTM_DELLINK 129 
#define  RTM_NEWLINK 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int link_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  link_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int link_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning (char*,int) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  netdev_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int netdev_set_ifindex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 
 int sd_netlink_message_get_type (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sd_netlink_message_is_error (int /*<<< orphan*/ *) ; 
 int sd_netlink_message_read_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int sd_rtnl_message_link_get_ifindex (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int manager_rtnl_process_link(sd_netlink *rtnl, sd_netlink_message *message, void *userdata) {
        Manager *m = userdata;
        Link *link = NULL;
        NetDev *netdev = NULL;
        uint16_t type;
        const char *name;
        int r, ifindex;

        assert(rtnl);
        assert(message);
        assert(m);

        if (sd_netlink_message_is_error(message)) {
                r = sd_netlink_message_get_errno(message);
                if (r < 0)
                        log_warning_errno(r, "rtnl: Could not receive link message, ignoring: %m");

                return 0;
        }

        r = sd_netlink_message_get_type(message, &type);
        if (r < 0) {
                log_warning_errno(r, "rtnl: Could not get message type, ignoring: %m");
                return 0;
        } else if (!IN_SET(type, RTM_NEWLINK, RTM_DELLINK)) {
                log_warning("rtnl: Received unexpected message type %u when processing link, ignoring.", type);
                return 0;
        }

        r = sd_rtnl_message_link_get_ifindex(message, &ifindex);
        if (r < 0) {
                log_warning_errno(r, "rtnl: Could not get ifindex from link message, ignoring: %m");
                return 0;
        } else if (ifindex <= 0) {
                log_warning("rtnl: received link message with invalid ifindex %d, ignoring.", ifindex);
                return 0;
        }

        r = sd_netlink_message_read_string(message, IFLA_IFNAME, &name);
        if (r < 0) {
                log_warning_errno(r, "rtnl: Received link message without ifname, ignoring: %m");
                return 0;
        }

        (void) link_get(m, ifindex, &link);
        (void) netdev_get(m, name, &netdev);

        switch (type) {
        case RTM_NEWLINK:
                if (!link) {
                        /* link is new, so add it */
                        r = link_add(m, message, &link);
                        if (r < 0) {
                                log_warning_errno(r, "Could not process new link message, ignoring: %m");
                                return 0;
                        }
                }

                if (netdev) {
                        /* netdev exists, so make sure the ifindex matches */
                        r = netdev_set_ifindex(netdev, message);
                        if (r < 0) {
                                log_warning_errno(r, "Could not process new link message for netdev, ignoring: %m");
                                return 0;
                        }
                }

                r = link_update(link, message);
                if (r < 0) {
                        log_warning_errno(r, "Could not process link message, ignoring: %m");
                        return 0;
                }

                break;

        case RTM_DELLINK:
                link_drop(link);
                netdev_drop(netdev);

                break;

        default:
                assert_not_reached("Received link message with invalid RTNL message type.");
        }

        return 1;
}