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
typedef  int /*<<< orphan*/  NetDev ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/ * WIREGUARD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_endpoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireguard_set_interface (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_wireguard_post_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        assert(netdev);
        assert(WIREGUARD(netdev));

        (void) wireguard_set_interface(netdev);
        resolve_endpoints(netdev);
        return 0;
}