#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 scalar_t__ NETDEV_STATE_LINGER ; 
 int /*<<< orphan*/  log_netdev_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netdev_callbacks_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_detach_from_manager (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_unref (TYPE_1__*) ; 

void netdev_drop(NetDev *netdev) {
        if (!netdev || netdev->state == NETDEV_STATE_LINGER)
                return;

        netdev->state = NETDEV_STATE_LINGER;

        log_netdev_debug(netdev, "netdev removed");

        netdev_callbacks_clear(netdev);

        netdev_detach_from_manager(netdev);

        netdev_unref(netdev);

        return;
}