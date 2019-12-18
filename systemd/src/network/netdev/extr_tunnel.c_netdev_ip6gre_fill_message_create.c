#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_21__ {int /*<<< orphan*/  in6; } ;
struct TYPE_20__ {int /*<<< orphan*/  in6; } ;
struct TYPE_22__ {scalar_t__ kind; scalar_t__ ipv6_flowlabel; scalar_t__ flags; scalar_t__ key; scalar_t__ ikey; scalar_t__ okey; int /*<<< orphan*/  ttl; TYPE_2__ remote; TYPE_1__ local; scalar_t__ assign_to_loopback; } ;
typedef  TYPE_3__ sd_netlink_message ;
typedef  TYPE_3__ Tunnel ;
struct TYPE_23__ {scalar_t__ ifindex; } ;
typedef  TYPE_3__ NetDev ;
typedef  TYPE_6__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  GRE_KEY ; 
 int /*<<< orphan*/  IFLA_GRE_FLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_FLOWINFO ; 
 int /*<<< orphan*/  IFLA_GRE_IFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_IKEY ; 
 int /*<<< orphan*/  IFLA_GRE_LINK ; 
 int /*<<< orphan*/  IFLA_GRE_LOCAL ; 
 int /*<<< orphan*/  IFLA_GRE_OFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_OKEY ; 
 int /*<<< orphan*/  IFLA_GRE_REMOTE ; 
 int /*<<< orphan*/  IFLA_GRE_TTL ; 
 TYPE_3__* IP6GRE (TYPE_3__*) ; 
 TYPE_3__* IP6GRETAP (TYPE_3__*) ; 
 scalar_t__ LOOPBACK_IFINDEX ; 
 scalar_t__ NETDEV_KIND_IP6GRE ; 
 scalar_t__ _NETDEV_IPV6_FLOWLABEL_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 scalar_t__ htobe32 (scalar_t__) ; 
 int log_netdev_error_errno (TYPE_3__*,int,char*) ; 
 int sd_netlink_message_append_in6_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_u16 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_append_u32 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u8 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_ip6gre_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        uint32_t ikey = 0;
        uint32_t okey = 0;
        uint16_t iflags = 0;
        uint16_t oflags = 0;
        Tunnel *t;
        int r;

        assert(netdev);

        if (netdev->kind == NETDEV_KIND_IP6GRE)
                t = IP6GRE(netdev);
        else
                t = IP6GRETAP(netdev);

        assert(t);
        assert(m);

        if (link || t->assign_to_loopback) {
                r = sd_netlink_message_append_u32(m, IFLA_GRE_LINK, link ? link->ifindex : LOOPBACK_IFINDEX);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_LINK attribute: %m");
        }

        r = sd_netlink_message_append_in6_addr(m, IFLA_GRE_LOCAL, &t->local.in6);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_LOCAL attribute: %m");

        r = sd_netlink_message_append_in6_addr(m, IFLA_GRE_REMOTE, &t->remote.in6);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_REMOTE attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_GRE_TTL, t->ttl);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_TTL attribute: %m");

        if (t->ipv6_flowlabel != _NETDEV_IPV6_FLOWLABEL_INVALID) {
                r = sd_netlink_message_append_u32(m, IFLA_GRE_FLOWINFO, t->ipv6_flowlabel);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_FLOWINFO attribute: %m");
        }

        r = sd_netlink_message_append_u32(m, IFLA_GRE_FLAGS, t->flags);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_FLAGS attribute: %m");

        if (t->key != 0) {
                ikey = okey = htobe32(t->key);
                iflags |= GRE_KEY;
                oflags |= GRE_KEY;
        }

        if (t->ikey != 0) {
                ikey = htobe32(t->ikey);
                iflags |= GRE_KEY;
        }

        if (t->okey != 0) {
                okey = htobe32(t->okey);
                oflags |= GRE_KEY;
        }

        r = sd_netlink_message_append_u32(m, IFLA_GRE_IKEY, ikey);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_IKEY attribute: %m");

        r = sd_netlink_message_append_u32(m, IFLA_GRE_OKEY, okey);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_OKEY attribute: %m");

        r = sd_netlink_message_append_u16(m, IFLA_GRE_IFLAGS, iflags);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_IFLAGS attribute: %m");

        r = sd_netlink_message_append_u16(m, IFLA_GRE_OFLAGS, oflags);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_OFLAGS, attribute: %m");

        return r;
}