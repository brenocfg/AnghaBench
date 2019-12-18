#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  create_type; } ;
typedef  int /*<<< orphan*/  NetDevCreateType ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 TYPE_1__* NETDEV_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static inline NetDevCreateType netdev_get_create_type(NetDev *netdev) {
        assert(netdev);
        assert(NETDEV_VTABLE(netdev));

        return NETDEV_VTABLE(netdev)->create_type;
}