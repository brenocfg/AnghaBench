#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
struct TYPE_6__ {int stats_updated; int /*<<< orphan*/  stats_new; int /*<<< orphan*/  stats_old; } ;
struct TYPE_5__ {int /*<<< orphan*/  links; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IFLA_STATS64 ; 
 int /*<<< orphan*/  INT_TO_PTR (int) ; 
 scalar_t__ RTM_NEWLINK ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_get_type (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_netlink_message_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sd_rtnl_message_link_get_ifindex (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int process_message(Manager *manager, sd_netlink_message *message) {
        uint16_t type;
        int ifindex, r;
        Link *link;

        r = sd_netlink_message_get_type(message, &type);
        if (r < 0)
                return r;

        if (type != RTM_NEWLINK)
                return 0;

        r = sd_rtnl_message_link_get_ifindex(message, &ifindex);
        if (r < 0)
                return r;

        link = hashmap_get(manager->links, INT_TO_PTR(ifindex));
        if (!link)
                return -ENODEV;

        link->stats_old = link->stats_new;

        r = sd_netlink_message_read(message, IFLA_STATS64, sizeof link->stats_new, &link->stats_new);
        if (r < 0)
                return r;

        link->stats_updated = true;

        return 0;
}