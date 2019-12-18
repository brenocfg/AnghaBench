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
struct TYPE_7__ {int udp6_csum_rx; int udp6_csum_tx; int /*<<< orphan*/  l2tp_encap_type; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ L2tpTunnel ;

/* Variables and functions */
 TYPE_1__* L2TP (TYPE_1__*) ; 
 int /*<<< orphan*/  NETDEV_L2TP_ENCAPTYPE_UDP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void l2tp_tunnel_init(NetDev *netdev) {
        L2tpTunnel *t;

        assert(netdev);

        t = L2TP(netdev);

        assert(t);

        t->l2tp_encap_type = NETDEV_L2TP_ENCAPTYPE_UDP;
        t->udp6_csum_rx = true;
        t->udp6_csum_tx = true;
}