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
 int EEXIST ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_enter_failed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_link_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_link_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int link_set_handler(sd_netlink *rtnl, sd_netlink_message *m, Link *link) {
        int r;

        assert(link);

        log_link_debug(link, "Set link");

        r = sd_netlink_message_get_errno(m);
        if (r < 0 && r != -EEXIST) {
                log_link_error_errno(link, r, "Failed to configure CAN link: %m");
                link_enter_failed(link);
        }

        return 1;
}