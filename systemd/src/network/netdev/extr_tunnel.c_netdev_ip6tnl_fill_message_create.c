#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  in6; } ;
struct TYPE_17__ {int /*<<< orphan*/  in6; } ;
struct TYPE_19__ {scalar_t__ ttl; scalar_t__ ipv6_flowlabel; scalar_t__ flags; scalar_t__ allow_localremote; scalar_t__ encap_limit; int ip6tnl_mode; scalar_t__ copy_dscp; TYPE_2__ remote; TYPE_1__ local; scalar_t__ assign_to_loopback; } ;
typedef  TYPE_3__ sd_netlink_message ;
typedef  TYPE_3__ Tunnel ;
struct TYPE_20__ {scalar_t__ ifindex; } ;
typedef  TYPE_3__ NetDev ;
typedef  TYPE_6__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_IPTUN_ENCAP_LIMIT ; 
 int /*<<< orphan*/  IFLA_IPTUN_FLAGS ; 
 int /*<<< orphan*/  IFLA_IPTUN_FLOWINFO ; 
 int /*<<< orphan*/  IFLA_IPTUN_LINK ; 
 int /*<<< orphan*/  IFLA_IPTUN_LOCAL ; 
 int /*<<< orphan*/  IFLA_IPTUN_PROTO ; 
 int /*<<< orphan*/  IFLA_IPTUN_REMOTE ; 
 int /*<<< orphan*/  IFLA_IPTUN_TTL ; 
 TYPE_3__* IP6TNL (TYPE_3__*) ; 
 int /*<<< orphan*/  IP6_TNL_F_ALLOW_LOCAL_REMOTE ; 
 scalar_t__ IP6_TNL_F_RCV_DSCP_COPY ; 
 scalar_t__ IPPROTO_IPIP ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPV6_DEFAULT_TNL_ENCAP_LIMIT ; 
 scalar_t__ LOOPBACK_IFINDEX ; 
#define  NETDEV_IP6_TNL_MODE_ANYIP6 130 
#define  NETDEV_IP6_TNL_MODE_IP6IP6 129 
#define  NETDEV_IP6_TNL_MODE_IPIP6 128 
 int /*<<< orphan*/  SET_FLAG (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _NETDEV_IPV6_FLOWLABEL_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int log_netdev_error_errno (TYPE_3__*,int,char*) ; 
 int sd_netlink_message_append_in6_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_u32 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u8 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int netdev_ip6tnl_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        Tunnel *t = IP6TNL(netdev);
        uint8_t proto;
        int r;

        assert(netdev);
        assert(m);
        assert(t);

        if (link || t->assign_to_loopback) {
                r = sd_netlink_message_append_u32(m, IFLA_IPTUN_LINK, link ? link->ifindex : LOOPBACK_IFINDEX);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_LINK attribute: %m");
        }

        r = sd_netlink_message_append_in6_addr(m, IFLA_IPTUN_LOCAL, &t->local.in6);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_LOCAL attribute: %m");

        r = sd_netlink_message_append_in6_addr(m, IFLA_IPTUN_REMOTE, &t->remote.in6);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_REMOTE attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_IPTUN_TTL, t->ttl);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_TTL attribute: %m");

        if (t->ipv6_flowlabel != _NETDEV_IPV6_FLOWLABEL_INVALID) {
                r = sd_netlink_message_append_u32(m, IFLA_IPTUN_FLOWINFO, t->ipv6_flowlabel);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_FLOWINFO attribute: %m");
        }

        if (t->copy_dscp)
                t->flags |= IP6_TNL_F_RCV_DSCP_COPY;

        if (t->allow_localremote >= 0)
                SET_FLAG(t->flags, IP6_TNL_F_ALLOW_LOCAL_REMOTE, t->allow_localremote);

        if (t->encap_limit != IPV6_DEFAULT_TNL_ENCAP_LIMIT) {
                r = sd_netlink_message_append_u8(m, IFLA_IPTUN_ENCAP_LIMIT, t->encap_limit);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_ENCAP_LIMIT attribute: %m");
        }

        r = sd_netlink_message_append_u32(m, IFLA_IPTUN_FLAGS, t->flags);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_FLAGS attribute: %m");

        switch (t->ip6tnl_mode) {
        case NETDEV_IP6_TNL_MODE_IP6IP6:
                proto = IPPROTO_IPV6;
                break;
        case NETDEV_IP6_TNL_MODE_IPIP6:
                proto = IPPROTO_IPIP;
                break;
        case NETDEV_IP6_TNL_MODE_ANYIP6:
        default:
                proto = 0;
                break;
        }

        r = sd_netlink_message_append_u8(m, IFLA_IPTUN_PROTO, proto);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_PROTO attribute: %m");

        return r;
}