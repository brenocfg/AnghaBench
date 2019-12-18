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
struct TYPE_10__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  links_by_name; struct TYPE_10__* manager; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,char*) ; 
 int hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_read_string (TYPE_1__*,int /*<<< orphan*/ ,char const**) ; 
 int sd_rtnl_message_link_get_flags (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char const*) ; 

int link_update_rtnl(Link *l, sd_netlink_message *m) {
        const char *ifname;
        int r;

        assert(l);
        assert(l->manager);
        assert(m);

        r = sd_rtnl_message_link_get_flags(m, &l->flags);
        if (r < 0)
                return r;

        r = sd_netlink_message_read_string(m, IFLA_IFNAME, &ifname);
        if (r < 0)
                return r;

        if (!streq(l->ifname, ifname)) {
                char *new_ifname;

                new_ifname = strdup(ifname);
                if (!new_ifname)
                        return -ENOMEM;

                assert_se(hashmap_remove(l->manager->links_by_name, l->ifname) == l);
                free_and_replace(l->ifname, new_ifname);

                r = hashmap_put(l->manager->links_by_name, l->ifname, l);
                if (r < 0)
                        return r;
        }

        return 0;
}