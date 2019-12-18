#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_10__ {scalar_t__ dhcp4_messages; int dhcp4_configured; int /*<<< orphan*/  manager; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp4_release_old_lease (TYPE_1__*) ; 
 int /*<<< orphan*/  link_check_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int link_request_set_routes (TYPE_1__*) ; 
 int link_set_dhcp_routes (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_error_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  manager_rtnl_process_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dhcp4_address_handler(sd_netlink *rtnl, sd_netlink_message *m, Link *link) {
        int r;

        assert(link);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return 1;

        r = sd_netlink_message_get_errno(m);
        if (r < 0 && r != -EEXIST) {
                log_link_error_errno(link, r, "Could not set DHCPv4 address: %m");
                link_enter_failed(link);
                return 1;
        } else if (r >= 0)
                (void) manager_rtnl_process_address(rtnl, m, link->manager);

        r = link_set_dhcp_routes(link);
        if (r < 0) {
                link_enter_failed(link);
                return 1;
        }

        /* Add back static routes since kernel removes while DHCPv4 address is removed from when lease expires */
        r = link_request_set_routes(link);
        if (r < 0) {
                link_enter_failed(link);
                return 1;
        }

        if (link->dhcp4_messages == 0) {
                link->dhcp4_configured = true;
                /* The new address is configured, and no route is requested.
                 * Let's drop the old lease. */
                dhcp4_release_old_lease(link);
                link_check_ready(link);
        }

        return 1;
}