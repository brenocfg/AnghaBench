#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_23__ {int /*<<< orphan*/  in; } ;
struct TYPE_22__ {int /*<<< orphan*/  in; } ;
struct TYPE_24__ {int kind; scalar_t__ key; scalar_t__ ikey; scalar_t__ okey; scalar_t__ gre_erspan_sequence; int /*<<< orphan*/  fou_destination_port; int /*<<< orphan*/  encap_src_port; int /*<<< orphan*/  fou_encap_type; scalar_t__ fou_tunnel; int /*<<< orphan*/  pmtudisc; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; TYPE_2__ remote; TYPE_1__ local; int /*<<< orphan*/  erspan_index; scalar_t__ assign_to_loopback; } ;
typedef  TYPE_3__ sd_netlink_message ;
typedef  TYPE_3__ Tunnel ;
struct TYPE_25__ {int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_3__ NetDev ;
typedef  TYPE_6__ Link ;

/* Variables and functions */
 TYPE_3__* ERSPAN (TYPE_3__*) ; 
 TYPE_3__* GRE (TYPE_3__*) ; 
 TYPE_3__* GRETAP (TYPE_3__*) ; 
 int /*<<< orphan*/  GRE_KEY ; 
 int /*<<< orphan*/  GRE_SEQ ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_DPORT ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_SPORT ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_TYPE ; 
 int /*<<< orphan*/  IFLA_GRE_ERSPAN_INDEX ; 
 int /*<<< orphan*/  IFLA_GRE_IFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_IKEY ; 
 int /*<<< orphan*/  IFLA_GRE_LINK ; 
 int /*<<< orphan*/  IFLA_GRE_LOCAL ; 
 int /*<<< orphan*/  IFLA_GRE_OFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_OKEY ; 
 int /*<<< orphan*/  IFLA_GRE_PMTUDISC ; 
 int /*<<< orphan*/  IFLA_GRE_REMOTE ; 
 int /*<<< orphan*/  IFLA_GRE_TOS ; 
 int /*<<< orphan*/  IFLA_GRE_TTL ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
#define  NETDEV_KIND_ERSPAN 130 
#define  NETDEV_KIND_GRE 129 
#define  NETDEV_KIND_GRETAP 128 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (scalar_t__) ; 
 int log_netdev_error_errno (TYPE_3__*,int,char*) ; 
 int sd_netlink_message_append_in_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_u16 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_append_u32 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_append_u8 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_gre_erspan_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        uint32_t ikey = 0;
        uint32_t okey = 0;
        uint16_t iflags = 0;
        uint16_t oflags = 0;
        Tunnel *t;
        int r;

        assert(netdev);
        assert(m);

        switch (netdev->kind) {
        case NETDEV_KIND_GRE:
                t = GRE(netdev);
                break;
        case NETDEV_KIND_ERSPAN:
                t = ERSPAN(netdev);
                break;
        case NETDEV_KIND_GRETAP:
                t = GRETAP(netdev);
                break;
        default:
                assert_not_reached("invalid netdev kind");
        }

        assert(t);

        if (link || t->assign_to_loopback) {
                r = sd_netlink_message_append_u32(m, IFLA_GRE_LINK, link ? link->ifindex : LOOPBACK_IFINDEX);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_LINK attribute: %m");
        }

        if (netdev->kind == NETDEV_KIND_ERSPAN) {
                r = sd_netlink_message_append_u32(m, IFLA_GRE_ERSPAN_INDEX, t->erspan_index);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_ERSPAN_INDEX attribute: %m");
        }

        r = sd_netlink_message_append_in_addr(m, IFLA_GRE_LOCAL, &t->local.in);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_LOCAL attribute: %m");

        r = sd_netlink_message_append_in_addr(m, IFLA_GRE_REMOTE, &t->remote.in);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_REMOTE attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_GRE_TTL, t->ttl);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_TTL attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_GRE_TOS, t->tos);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_TOS attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_GRE_PMTUDISC, t->pmtudisc);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_PMTUDISC attribute: %m");

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

        if (t->gre_erspan_sequence > 0) {
                iflags |= GRE_SEQ;
                oflags |= GRE_SEQ;
        } else if (t->gre_erspan_sequence == 0) {
                iflags &= ~GRE_SEQ;
                oflags &= ~GRE_SEQ;
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

        if (t->fou_tunnel) {
                r = sd_netlink_message_append_u16(m, IFLA_GRE_ENCAP_TYPE, t->fou_encap_type);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_ENCAP_TYPE attribute: %m");

                r = sd_netlink_message_append_u16(m, IFLA_GRE_ENCAP_SPORT, htobe16(t->encap_src_port));
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_ENCAP_SPORT attribute: %m");

                r = sd_netlink_message_append_u16(m, IFLA_GRE_ENCAP_DPORT, htobe16(t->fou_destination_port));
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_GRE_ENCAP_DPORT attribute: %m");
        }

        return r;
}