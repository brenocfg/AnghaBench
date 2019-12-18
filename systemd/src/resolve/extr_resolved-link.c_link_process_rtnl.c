#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  operstate; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_MTU ; 
 int /*<<< orphan*/  IFLA_OPERSTATE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  link_add_rrs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  link_allocate_scopes (TYPE_1__*) ; 
 scalar_t__ sd_netlink_message_read_string (TYPE_1__*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  sd_netlink_message_read_u32 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_netlink_message_read_u8 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_rtnl_message_link_get_flags (TYPE_1__*,int /*<<< orphan*/ *) ; 

int link_process_rtnl(Link *l, sd_netlink_message *m) {
        const char *n = NULL;
        int r;

        assert(l);
        assert(m);

        r = sd_rtnl_message_link_get_flags(m, &l->flags);
        if (r < 0)
                return r;

        (void) sd_netlink_message_read_u32(m, IFLA_MTU, &l->mtu);
        (void) sd_netlink_message_read_u8(m, IFLA_OPERSTATE, &l->operstate);

        if (sd_netlink_message_read_string(m, IFLA_IFNAME, &n) >= 0) {
                r = free_and_strdup(&l->ifname, n);
                if (r < 0)
                        return r;
        }

        link_allocate_scopes(l);
        link_add_rrs(l, false);

        return 0;
}