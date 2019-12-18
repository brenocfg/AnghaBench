#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_6__ {int /*<<< orphan*/  dhcp_client; int /*<<< orphan*/  manager; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp_lease_renew (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_debug_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  manager_rtnl_process_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dhcp_remove_address_handler(sd_netlink *rtnl, sd_netlink_message *m, Link *link) {
        int r;

        assert(link);

        /* This is only used when retrying to assign the address received from DHCPv4 server.
         * See dhcp4_route_handler(). */

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return 1;

        r = sd_netlink_message_get_errno(m);
        if (r < 0)
                log_link_debug_errno(link, r, "Failed to remove DHCPv4 address, ignoring: %m");
        else
                (void) manager_rtnl_process_address(rtnl, m, link->manager);

        (void) dhcp_lease_renew(link->dhcp_client, link);
        return 1;
}