#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_22__ {int /*<<< orphan*/  in; } ;
struct TYPE_21__ {int /*<<< orphan*/  in; } ;
struct TYPE_23__ {scalar_t__ kind; scalar_t__ fou_encap_type; scalar_t__ sixrd_prefixlen; scalar_t__ isatap; int /*<<< orphan*/  sixrd_prefix; int /*<<< orphan*/  fou_destination_port; int /*<<< orphan*/  encap_src_port; scalar_t__ fou_tunnel; int /*<<< orphan*/  pmtudisc; int /*<<< orphan*/  ttl; TYPE_2__ remote; TYPE_1__ local; scalar_t__ assign_to_loopback; } ;
typedef  TYPE_3__ sd_netlink_message ;
typedef  TYPE_3__ Tunnel ;
struct TYPE_24__ {int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_3__ NetDev ;
typedef  TYPE_6__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_IPTUN_6RD_PREFIX ; 
 int /*<<< orphan*/  IFLA_IPTUN_6RD_PREFIXLEN ; 
 int /*<<< orphan*/  IFLA_IPTUN_ENCAP_DPORT ; 
 int /*<<< orphan*/  IFLA_IPTUN_ENCAP_SPORT ; 
 int /*<<< orphan*/  IFLA_IPTUN_ENCAP_TYPE ; 
 int /*<<< orphan*/  IFLA_IPTUN_FLAGS ; 
 int /*<<< orphan*/  IFLA_IPTUN_LINK ; 
 int /*<<< orphan*/  IFLA_IPTUN_LOCAL ; 
 int /*<<< orphan*/  IFLA_IPTUN_PMTUDISC ; 
 int /*<<< orphan*/  IFLA_IPTUN_REMOTE ; 
 int /*<<< orphan*/  IFLA_IPTUN_TTL ; 
 TYPE_3__* IPIP (TYPE_3__*) ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 scalar_t__ NETDEV_KIND_IPIP ; 
 scalar_t__ NETDEV_KIND_SIT ; 
 int /*<<< orphan*/  SET_FLAG (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* SIT (TYPE_3__*) ; 
 int /*<<< orphan*/  SIT_ISATAP ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 scalar_t__ htobe16 (int /*<<< orphan*/ ) ; 
 int log_netdev_error_errno (TYPE_3__*,int,char*) ; 
 int sd_netlink_message_append_in6_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_in_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_u16 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u32 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_append_u8 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_ipip_sit_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        Tunnel *t;
        int r;

        assert(netdev);

        if (netdev->kind == NETDEV_KIND_IPIP)
                t = IPIP(netdev);
        else
                t = SIT(netdev);

        assert(m);
        assert(t);

        if (link || t->assign_to_loopback) {
                r = sd_netlink_message_append_u32(m, IFLA_IPTUN_LINK, link ? link->ifindex : LOOPBACK_IFINDEX);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_LINK attribute: %m");
        }

        r = sd_netlink_message_append_in_addr(m, IFLA_IPTUN_LOCAL, &t->local.in);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_LOCAL attribute: %m");

        r = sd_netlink_message_append_in_addr(m, IFLA_IPTUN_REMOTE, &t->remote.in);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_REMOTE attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_IPTUN_TTL, t->ttl);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_TTL attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_IPTUN_PMTUDISC, t->pmtudisc);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_PMTUDISC attribute: %m");

        if (t->fou_tunnel) {
                r = sd_netlink_message_append_u16(m, IFLA_IPTUN_ENCAP_TYPE, t->fou_encap_type);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_ENCAP_TYPE attribute: %m");

                r = sd_netlink_message_append_u16(m, IFLA_IPTUN_ENCAP_SPORT, htobe16(t->encap_src_port));
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_ENCAP_SPORT attribute: %m");

                r = sd_netlink_message_append_u16(m, IFLA_IPTUN_ENCAP_DPORT, htobe16(t->fou_destination_port));
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_ENCAP_DPORT attribute: %m");
        }

        if (netdev->kind == NETDEV_KIND_SIT) {
                if (t->sixrd_prefixlen > 0) {
                        r = sd_netlink_message_append_in6_addr(m, IFLA_IPTUN_6RD_PREFIX, &t->sixrd_prefix);
                        if (r < 0)
                                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_6RD_PREFIX attribute: %m");

                        /* u16 is deliberate here, even though we're passing a netmask that can never be >128. The kernel is
                         * expecting to receive the prefixlen as a u16.
                         */
                        r = sd_netlink_message_append_u16(m, IFLA_IPTUN_6RD_PREFIXLEN, t->sixrd_prefixlen);
                        if (r < 0)
                                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_6RD_PREFIXLEN attribute: %m");
                }

                if (t->isatap >= 0) {
                        uint16_t flags = 0;

                        SET_FLAG(flags, SIT_ISATAP, t->isatap);

                        r = sd_netlink_message_append_u16(m, IFLA_IPTUN_FLAGS, flags);
                        if (r < 0)
                                return log_netdev_error_errno(netdev, r, "Could not append IFLA_IPTUN_FLAGS attribute: %m");
                }
        }

        return r;
}