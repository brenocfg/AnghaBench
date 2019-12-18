#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int setting_mtu; scalar_t__ state; struct TYPE_11__* ifname; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 scalar_t__ LINK_STATE_INITIALIZED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int link_configure_after_setting_mtu (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int sd_netlink_message_get_errno (TYPE_1__*) ; 

__attribute__((used)) static int set_mtu_handler(sd_netlink *rtnl, sd_netlink_message *m, Link *link) {
        int r;

        assert(m);
        assert(link);
        assert(link->ifname);

        link->setting_mtu = false;

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return 1;

        r = sd_netlink_message_get_errno(m);
        if (r < 0)
                log_link_warning_errno(link, r, "Could not set MTU, ignoring: %m");
        else
                log_link_debug(link, "Setting MTU done.");

        if (link->state == LINK_STATE_INITIALIZED) {
                r = link_configure_after_setting_mtu(link);
                if (r < 0)
                        link_enter_failed(link);
        }

        return 1;
}