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
struct TYPE_7__ {int allow_localremote; int /*<<< orphan*/  ipv6_flowlabel; int /*<<< orphan*/  ip6tnl_mode; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  ttl; } ;
typedef  TYPE_1__ Tunnel ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TNL_HOP_LIMIT ; 
 TYPE_1__* IP6TNL (TYPE_1__*) ; 
 int /*<<< orphan*/  IPV6_DEFAULT_TNL_ENCAP_LIMIT ; 
 int /*<<< orphan*/  _NETDEV_IP6_TNL_MODE_INVALID ; 
 int /*<<< orphan*/  _NETDEV_IPV6_FLOWLABEL_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void ip6tnl_init(NetDev *n) {
        Tunnel *t = IP6TNL(n);

        assert(n);
        assert(t);

        t->ttl = DEFAULT_TNL_HOP_LIMIT;
        t->encap_limit = IPV6_DEFAULT_TNL_ENCAP_LIMIT;
        t->ip6tnl_mode = _NETDEV_IP6_TNL_MODE_INVALID;
        t->ipv6_flowlabel = _NETDEV_IPV6_FLOWLABEL_INVALID;
        t->allow_localremote = -1;
}