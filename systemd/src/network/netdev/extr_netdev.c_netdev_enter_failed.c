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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_STATE_FAILED ; 
 int /*<<< orphan*/  netdev_callbacks_clear (TYPE_1__*) ; 

__attribute__((used)) static int netdev_enter_failed(NetDev *netdev) {
        netdev->state = NETDEV_STATE_FAILED;

        netdev_callbacks_clear(netdev);

        return 0;
}