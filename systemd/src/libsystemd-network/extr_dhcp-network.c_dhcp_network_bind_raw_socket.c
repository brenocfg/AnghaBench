#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ether_addr {TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_INFINIBAND ; 
 int EINVAL ; 
 size_t ETH_ALEN ; 
 size_t INFINIBAND_ALEN ; 
 int _bind_raw_socket (int,union sockaddr_union*,int /*<<< orphan*/ ,int const*,size_t,int const*,struct ether_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_return (int,int) ; 
 int /*<<< orphan*/  memcpy (struct ether_addr*,int const*,size_t) ; 

int dhcp_network_bind_raw_socket(int ifindex, union sockaddr_union *link,
                                 uint32_t xid, const uint8_t *mac_addr,
                                 size_t mac_addr_len, uint16_t arp_type,
                                 uint16_t port) {
        static const uint8_t eth_bcast[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        /* Default broadcast address for IPoIB */
        static const uint8_t ib_bcast[] = {
                0x00, 0xff, 0xff, 0xff, 0xff, 0x12, 0x40, 0x1b,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0xff, 0xff, 0xff, 0xff
          };
        struct ether_addr eth_mac = { { 0, 0, 0, 0, 0, 0 } };
        const uint8_t *bcast_addr = NULL;
        uint8_t dhcp_hlen = 0;

        if (arp_type == ARPHRD_ETHER) {
                assert_return(mac_addr_len == ETH_ALEN, -EINVAL);
                memcpy(&eth_mac, mac_addr, ETH_ALEN);
                bcast_addr = eth_bcast;
                dhcp_hlen = ETH_ALEN;
        } else if (arp_type == ARPHRD_INFINIBAND) {
                assert_return(mac_addr_len == INFINIBAND_ALEN, -EINVAL);
                bcast_addr = ib_bcast;
        } else
                return -EINVAL;

        return _bind_raw_socket(ifindex, link, xid, mac_addr, mac_addr_len,
                                bcast_addr, &eth_mac, arp_type, dhcp_hlen, port);
}