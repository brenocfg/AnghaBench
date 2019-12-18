#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/  link_enter_failed (int /*<<< orphan*/ *) ; 
 int link_initialized_and_synced (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int link_initialized_handler(sd_netlink *rtnl, sd_netlink_message *m, Link *link) {
        int r;

        r = link_initialized_and_synced(link);
        if (r < 0)
                link_enter_failed(link);
        return 1;
}