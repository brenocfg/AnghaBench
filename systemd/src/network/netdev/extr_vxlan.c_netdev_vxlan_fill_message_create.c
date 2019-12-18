#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
struct ifla_vxlan_port_range {void* high; void* low; } ;
struct TYPE_22__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_21__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_23__ {scalar_t__ vni; scalar_t__ remote_family; scalar_t__ local_family; int ifindex; scalar_t__ ttl; scalar_t__ tos; scalar_t__ learning; scalar_t__ route_short_circuit; scalar_t__ arp_proxy; scalar_t__ l2miss; scalar_t__ l3miss; int fdb_ageing; int max_fdb; scalar_t__ udpcsum; scalar_t__ udp6zerocsumtx; scalar_t__ udp6zerocsumrx; scalar_t__ remote_csum_tx; scalar_t__ remote_csum_rx; scalar_t__ dest_port; scalar_t__ df; scalar_t__ generic_protocol_extension; scalar_t__ group_policy; int /*<<< orphan*/  flow_label; TYPE_1__ port_range; scalar_t__ inherit; TYPE_17__ local; TYPE_17__ remote; } ;
typedef  TYPE_2__ sd_netlink_message ;
typedef  int /*<<< orphan*/  port_range ;
typedef  TYPE_2__ VxLan ;
typedef  TYPE_2__ NetDev ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IFLA_VXLAN_AGEING ; 
 int /*<<< orphan*/  IFLA_VXLAN_DF ; 
 int /*<<< orphan*/  IFLA_VXLAN_GBP ; 
 int /*<<< orphan*/  IFLA_VXLAN_GPE ; 
 int /*<<< orphan*/  IFLA_VXLAN_GROUP ; 
 int /*<<< orphan*/  IFLA_VXLAN_GROUP6 ; 
 int /*<<< orphan*/  IFLA_VXLAN_ID ; 
 int /*<<< orphan*/  IFLA_VXLAN_L2MISS ; 
 int /*<<< orphan*/  IFLA_VXLAN_L3MISS ; 
 int /*<<< orphan*/  IFLA_VXLAN_LABEL ; 
 int /*<<< orphan*/  IFLA_VXLAN_LEARNING ; 
 int /*<<< orphan*/  IFLA_VXLAN_LIMIT ; 
 int /*<<< orphan*/  IFLA_VXLAN_LINK ; 
 int /*<<< orphan*/  IFLA_VXLAN_LOCAL ; 
 int /*<<< orphan*/  IFLA_VXLAN_LOCAL6 ; 
 int /*<<< orphan*/  IFLA_VXLAN_PORT ; 
 int /*<<< orphan*/  IFLA_VXLAN_PORT_RANGE ; 
 int /*<<< orphan*/  IFLA_VXLAN_PROXY ; 
 int /*<<< orphan*/  IFLA_VXLAN_REMCSUM_RX ; 
 int /*<<< orphan*/  IFLA_VXLAN_REMCSUM_TX ; 
 int /*<<< orphan*/  IFLA_VXLAN_RSC ; 
 int /*<<< orphan*/  IFLA_VXLAN_TOS ; 
 int /*<<< orphan*/  IFLA_VXLAN_TTL ; 
 int /*<<< orphan*/  IFLA_VXLAN_TTL_INHERIT ; 
 int /*<<< orphan*/  IFLA_VXLAN_UDP_CSUM ; 
 int /*<<< orphan*/  IFLA_VXLAN_UDP_ZERO_CSUM6_RX ; 
 int /*<<< orphan*/  IFLA_VXLAN_UDP_ZERO_CSUM6_TX ; 
 int USEC_PER_SEC ; 
 TYPE_2__* VXLAN (TYPE_2__*) ; 
 scalar_t__ VXLAN_VID_MAX ; 
 scalar_t__ _NETDEV_VXLAN_DF_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 void* htobe16 (scalar_t__) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 scalar_t__ in_addr_is_null (scalar_t__,TYPE_17__*) ; 
 int log_netdev_error_errno (TYPE_2__*,int,char*) ; 
 int sd_netlink_message_append_data (TYPE_2__*,int /*<<< orphan*/ ,struct ifla_vxlan_port_range*,int) ; 
 int sd_netlink_message_append_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_append_in6_addr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_in_addr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_netlink_message_append_u16 (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int sd_netlink_message_append_u32 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int sd_netlink_message_append_u8 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int netdev_vxlan_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        VxLan *v;
        int r;

        assert(netdev);
        assert(link);
        assert(m);

        v = VXLAN(netdev);

        assert(v);

        if (v->vni <= VXLAN_VID_MAX) {
                r = sd_netlink_message_append_u32(m, IFLA_VXLAN_ID, v->vni);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_ID attribute: %m");
        }

        if (in_addr_is_null(v->remote_family, &v->remote) == 0) {
                if (v->remote_family == AF_INET)
                        r = sd_netlink_message_append_in_addr(m, IFLA_VXLAN_GROUP, &v->remote.in);
                else
                        r = sd_netlink_message_append_in6_addr(m, IFLA_VXLAN_GROUP6, &v->remote.in6);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_GROUP attribute: %m");
        }

        if (in_addr_is_null(v->local_family, &v->local) == 0) {
                if (v->local_family == AF_INET)
                        r = sd_netlink_message_append_in_addr(m, IFLA_VXLAN_LOCAL, &v->local.in);
                else
                        r = sd_netlink_message_append_in6_addr(m, IFLA_VXLAN_LOCAL6, &v->local.in6);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_LOCAL attribute: %m");
        }

        r = sd_netlink_message_append_u32(m, IFLA_VXLAN_LINK, link->ifindex);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_LINK attribute: %m");

        if (v->inherit) {
                r = sd_netlink_message_append_flag(m, IFLA_VXLAN_TTL_INHERIT);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_TTL_INHERIT attribute: %m");
        } else {
                r = sd_netlink_message_append_u8(m, IFLA_VXLAN_TTL, v->ttl);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_TTL attribute: %m");
        }

        if (v->tos != 0) {
                r = sd_netlink_message_append_u8(m, IFLA_VXLAN_TOS, v->tos);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_TOS attribute: %m");
        }

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_LEARNING, v->learning);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_LEARNING attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_RSC, v->route_short_circuit);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_RSC attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_PROXY, v->arp_proxy);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_PROXY attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_L2MISS, v->l2miss);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_L2MISS attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_L3MISS, v->l3miss);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_L3MISS attribute: %m");

        if (v->fdb_ageing != 0) {
                r = sd_netlink_message_append_u32(m, IFLA_VXLAN_AGEING, v->fdb_ageing / USEC_PER_SEC);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_AGEING attribute: %m");
        }

        if (v->max_fdb != 0) {
                r = sd_netlink_message_append_u32(m, IFLA_VXLAN_LIMIT, v->max_fdb);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_LIMIT attribute: %m");
        }

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_UDP_CSUM, v->udpcsum);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_UDP_CSUM attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_UDP_ZERO_CSUM6_TX, v->udp6zerocsumtx);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_UDP_ZERO_CSUM6_TX attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_UDP_ZERO_CSUM6_RX, v->udp6zerocsumrx);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_UDP_ZERO_CSUM6_RX attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_REMCSUM_TX, v->remote_csum_tx);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_REMCSUM_TX attribute: %m");

        r = sd_netlink_message_append_u8(m, IFLA_VXLAN_REMCSUM_RX, v->remote_csum_rx);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_REMCSUM_RX attribute: %m");

        r = sd_netlink_message_append_u16(m, IFLA_VXLAN_PORT, htobe16(v->dest_port));
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_PORT attribute: %m");

        if (v->port_range.low != 0 || v->port_range.high != 0) {
                struct ifla_vxlan_port_range port_range;

                port_range.low = htobe16(v->port_range.low);
                port_range.high = htobe16(v->port_range.high);

                r = sd_netlink_message_append_data(m, IFLA_VXLAN_PORT_RANGE, &port_range, sizeof(port_range));
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_PORT_RANGE attribute: %m");
        }

        r = sd_netlink_message_append_u32(m, IFLA_VXLAN_LABEL, htobe32(v->flow_label));
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_LABEL attribute: %m");

        if (v->group_policy) {
                r = sd_netlink_message_append_flag(m, IFLA_VXLAN_GBP);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_GBP attribute: %m");
        }

        if (v->generic_protocol_extension) {
                r = sd_netlink_message_append_flag(m, IFLA_VXLAN_GPE);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_GPE attribute: %m");
        }

        if (v->df != _NETDEV_VXLAN_DF_INVALID) {
                r = sd_netlink_message_append_u8(m, IFLA_VXLAN_DF, v->df);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_VXLAN_DF attribute: %m");
        }

        return r;
}