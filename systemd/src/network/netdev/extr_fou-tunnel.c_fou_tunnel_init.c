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
struct TYPE_7__ {int /*<<< orphan*/  fou_encap_type; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ FouTunnel ;

/* Variables and functions */
 TYPE_1__* FOU (TYPE_1__*) ; 
 int /*<<< orphan*/  NETDEV_FOO_OVER_UDP_ENCAP_DIRECT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void fou_tunnel_init(NetDev *netdev) {
        FouTunnel *t;

        assert(netdev);

        t = FOU(netdev);

        assert(t);

        t->fou_encap_type = NETDEV_FOO_OVER_UDP_ENCAP_DIRECT;
}