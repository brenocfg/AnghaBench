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
typedef  int /*<<< orphan*/  NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_netdev_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_netdev_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_bridge_set_handler(sd_netlink *rtnl, sd_netlink_message *m, NetDev *netdev) {
        int r;

        assert(netdev);
        assert(m);

        r = sd_netlink_message_get_errno(m);
        if (r < 0) {
                log_netdev_warning_errno(netdev, r, "Bridge parameters could not be set: %m");
                return 1;
        }

        log_netdev_debug(netdev, "Bridge parameters set success");

        return 1;
}