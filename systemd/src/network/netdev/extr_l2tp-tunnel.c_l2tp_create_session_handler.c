#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_5__ {int /*<<< orphan*/  name; struct TYPE_5__* tunnel; } ;
typedef  int /*<<< orphan*/  NetDev ;
typedef  TYPE_1__ L2tpSession ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/ * NETDEV (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_netdev_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_netdev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_netdev_warning_errno (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_create_session_handler(sd_netlink *rtnl, sd_netlink_message *m, L2tpSession *session) {
        NetDev *netdev;
        int r;

        assert(session);
        assert(session->tunnel);

        netdev = NETDEV(session->tunnel);

        r = sd_netlink_message_get_errno(m);
        if (r == -EEXIST)
                log_netdev_info(netdev, "L2TP session %s exists, using existing without changing its parameters",
                                session->name);
        else if (r < 0) {
                log_netdev_warning_errno(netdev, r, "L2TP session %s could not be created: %m", session->name);
                return 1;
        }

        log_netdev_debug(netdev, "L2TP session %s created", session->name);
        return 1;
}