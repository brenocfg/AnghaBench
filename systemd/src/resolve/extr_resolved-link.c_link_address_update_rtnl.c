#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  link; int /*<<< orphan*/  scope; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ LinkAddress ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_add_rrs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link_allocate_scopes (int /*<<< orphan*/ ) ; 
 int sd_rtnl_message_addr_get_flags (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_rtnl_message_addr_get_scope (TYPE_1__*,int /*<<< orphan*/ *) ; 

int link_address_update_rtnl(LinkAddress *a, sd_netlink_message *m) {
        int r;
        assert(a);
        assert(m);

        r = sd_rtnl_message_addr_get_flags(m, &a->flags);
        if (r < 0)
                return r;

        sd_rtnl_message_addr_get_scope(m, &a->scope);

        link_allocate_scopes(a->link);
        link_add_rrs(a->link, false);

        return 0;
}