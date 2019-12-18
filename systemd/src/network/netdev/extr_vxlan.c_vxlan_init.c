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
struct TYPE_7__ {int learning; int udpcsum; int udp6zerocsumtx; int udp6zerocsumrx; int /*<<< orphan*/  df; scalar_t__ vni; } ;
typedef  TYPE_1__ VxLan ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 TYPE_1__* VXLAN (TYPE_1__*) ; 
 scalar_t__ VXLAN_VID_MAX ; 
 int /*<<< orphan*/  _NETDEV_VXLAN_DF_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void vxlan_init(NetDev *netdev) {
        VxLan *v;

        assert(netdev);

        v = VXLAN(netdev);

        assert(v);

        v->vni = VXLAN_VID_MAX + 1;
        v->df = _NETDEV_VXLAN_DF_INVALID;
        v->learning = true;
        v->udpcsum = false;
        v->udp6zerocsumtx = false;
        v->udp6zerocsumrx = false;
}