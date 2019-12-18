#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_18__ {int /*<<< orphan*/  links; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ sd_netlink ;
struct TYPE_19__ {int ifindex; int /*<<< orphan*/  ifname; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_4__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int) ; 
#define  RTM_DELLINK 129 
#define  RTM_NEWLINK 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_4__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_free (TYPE_4__*) ; 
 int link_new (TYPE_1__*,TYPE_4__**,int) ; 
 int link_process_rtnl (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  link_remove_user (TYPE_4__*) ; 
 int link_update (TYPE_4__*) ; 
 int /*<<< orphan*/  log_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_netlink_message_get_type (TYPE_1__*,int*) ; 
 int sd_rtnl_message_link_get_ifindex (TYPE_1__*,int*) ; 

__attribute__((used)) static int manager_process_link(sd_netlink *rtnl, sd_netlink_message *mm, void *userdata) {
        Manager *m = userdata;
        uint16_t type;
        Link *l;
        int ifindex, r;

        assert(rtnl);
        assert(m);
        assert(mm);

        r = sd_netlink_message_get_type(mm, &type);
        if (r < 0)
                goto fail;

        r = sd_rtnl_message_link_get_ifindex(mm, &ifindex);
        if (r < 0)
                goto fail;

        l = hashmap_get(m->links, INT_TO_PTR(ifindex));

        switch (type) {

        case RTM_NEWLINK:{
                bool is_new = !l;

                if (!l) {
                        r = link_new(m, &l, ifindex);
                        if (r < 0)
                                goto fail;
                }

                r = link_process_rtnl(l, mm);
                if (r < 0)
                        goto fail;

                r = link_update(l);
                if (r < 0)
                        goto fail;

                if (is_new)
                        log_debug("Found new link %i/%s", ifindex, l->ifname);

                break;
        }

        case RTM_DELLINK:
                if (l) {
                        log_debug("Removing link %i/%s", l->ifindex, l->ifname);
                        link_remove_user(l);
                        link_free(l);
                }

                break;
        }

        return 0;

fail:
        log_warning_errno(r, "Failed to process RTNL link message: %m");
        return 0;
}