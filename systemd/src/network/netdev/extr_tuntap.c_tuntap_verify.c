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
struct TYPE_5__ {scalar_t__ mtu; int /*<<< orphan*/  kind; scalar_t__ mac; } ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_netdev_warning (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  netdev_kind_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tuntap_verify(NetDev *netdev, const char *filename) {
        assert(netdev);

        if (netdev->mtu != 0)
                log_netdev_warning(netdev,
                                   "MTUBytes= configured for %s device in %s will be ignored.\n"
                                   "Please set it in the corresponding .network file.",
                                   netdev_kind_to_string(netdev->kind), filename);

        if (netdev->mac)
                log_netdev_warning(netdev,
                                   "MACAddress= configured for %s device in %s will be ignored.\n"
                                   "Please set it in the corresponding .network file.",
                                   netdev_kind_to_string(netdev->kind), filename);

        return 0;
}