#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  event; int /*<<< orphan*/  rtnl; int /*<<< orphan*/  rtnl_event_source; int /*<<< orphan*/  network_monitor; int /*<<< orphan*/  network_monitor_event_source; int /*<<< orphan*/  links_by_name; int /*<<< orphan*/  links; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_free ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_network_monitor_unref (int /*<<< orphan*/ ) ; 

void manager_free(Manager *m) {
        if (!m)
                return;

        hashmap_free_with_destructor(m->links, link_free);
        hashmap_free(m->links_by_name);

        sd_event_source_unref(m->network_monitor_event_source);
        sd_network_monitor_unref(m->network_monitor);

        sd_event_source_unref(m->rtnl_event_source);
        sd_netlink_unref(m->rtnl);

        sd_event_unref(m->event);
        free(m);

        return;
}