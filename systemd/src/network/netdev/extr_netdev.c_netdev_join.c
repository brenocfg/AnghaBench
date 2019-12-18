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
typedef  int /*<<< orphan*/  link_netlink_message_handler_t ;
struct TYPE_8__ {struct TYPE_8__* rtnl; struct TYPE_8__* manager; } ;
typedef  TYPE_1__ NetDev ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
#define  NETDEV_CREATE_AFTER_CONFIGURED 130 
#define  NETDEV_CREATE_MASTER 129 
#define  NETDEV_CREATE_STACKED 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int netdev_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int netdev_create_after_configured (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int netdev_enslave (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int netdev_get_create_type (TYPE_1__*) ; 

int netdev_join(NetDev *netdev, Link *link, link_netlink_message_handler_t callback) {
        int r;

        assert(netdev);
        assert(netdev->manager);
        assert(netdev->manager->rtnl);

        switch (netdev_get_create_type(netdev)) {
        case NETDEV_CREATE_MASTER:
                r = netdev_enslave(netdev, link, callback);
                if (r < 0)
                        return r;

                break;
        case NETDEV_CREATE_STACKED:
                r = netdev_create(netdev, link, callback);
                if (r < 0)
                        return r;

                break;
        case NETDEV_CREATE_AFTER_CONFIGURED:
                r = netdev_create_after_configured(netdev, link);
                if (r < 0)
                        return r;
                break;
        default:
                assert_not_reached("Can not join independent netdev");
        }

        return 0;
}