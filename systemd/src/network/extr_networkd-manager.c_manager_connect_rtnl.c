#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rtnl; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  RCVBUF_SIZE ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  RTM_DELNEIGH ; 
 int /*<<< orphan*/  RTM_DELNEXTHOP ; 
 int /*<<< orphan*/  RTM_DELROUTE ; 
 int /*<<< orphan*/  RTM_DELRULE ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 int /*<<< orphan*/  RTM_NEWNEXTHOP ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTM_NEWRULE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_rtnl_process_address ; 
 int /*<<< orphan*/  manager_rtnl_process_link ; 
 int /*<<< orphan*/  manager_rtnl_process_neighbor ; 
 int /*<<< orphan*/  manager_rtnl_process_nexthop ; 
 int /*<<< orphan*/  manager_rtnl_process_route ; 
 int /*<<< orphan*/  manager_rtnl_process_rule ; 
 int sd_netlink_add_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int sd_netlink_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_inc_rcvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_open (int /*<<< orphan*/ *) ; 
 int sd_netlink_open_fd (int /*<<< orphan*/ *,int) ; 
 int systemd_netlink_fd () ; 

__attribute__((used)) static int manager_connect_rtnl(Manager *m) {
        int fd, r;

        assert(m);

        fd = systemd_netlink_fd();
        if (fd < 0)
                r = sd_netlink_open(&m->rtnl);
        else
                r = sd_netlink_open_fd(&m->rtnl, fd);
        if (r < 0)
                return r;

        r = sd_netlink_inc_rcvbuf(m->rtnl, RCVBUF_SIZE);
        if (r < 0)
                return r;

        r = sd_netlink_attach_event(m->rtnl, m->event, 0);
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWLINK, &manager_rtnl_process_link, NULL, m, "network-rtnl_process_link");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELLINK, &manager_rtnl_process_link, NULL, m, "network-rtnl_process_link");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWADDR, &manager_rtnl_process_address, NULL, m, "network-rtnl_process_address");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELADDR, &manager_rtnl_process_address, NULL, m, "network-rtnl_process_address");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWNEIGH, &manager_rtnl_process_neighbor, NULL, m, "network-rtnl_process_neighbor");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELNEIGH, &manager_rtnl_process_neighbor, NULL, m, "network-rtnl_process_neighbor");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWROUTE, &manager_rtnl_process_route, NULL, m, "network-rtnl_process_route");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELROUTE, &manager_rtnl_process_route, NULL, m, "network-rtnl_process_route");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWRULE, &manager_rtnl_process_rule, NULL, m, "network-rtnl_process_rule");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELRULE, &manager_rtnl_process_rule, NULL, m, "network-rtnl_process_rule");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_NEWNEXTHOP, &manager_rtnl_process_nexthop, NULL, m, "network-rtnl_process_nexthop");
        if (r < 0)
                return r;

        r = sd_netlink_add_match(m->rtnl, NULL, RTM_DELNEXTHOP, &manager_rtnl_process_nexthop, NULL, m, "network-rtnl_process_nexthop");
        if (r < 0)
                return r;

        return 0;
}