#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FAMILY ; 
 int /*<<< orphan*/  DHCP6_MESSAGE ; 
 int /*<<< orphan*/  DHCP6_STATUS ; 
 int /*<<< orphan*/  DHCP_USE_DOMAINS ; 
 int /*<<< orphan*/  DUP ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IPV6_PRIVACY_EXTENSIONS ; 
 int /*<<< orphan*/  LINK_OPERSTATE ; 
 int /*<<< orphan*/  LLDP_MODE ; 
 int /*<<< orphan*/  NETDEV_BOND_AD_SELECT ; 
 int /*<<< orphan*/  NETDEV_BOND_ARP_ALL_TARGETS ; 
 int /*<<< orphan*/  NETDEV_BOND_ARP_VALIDATE ; 
 int /*<<< orphan*/  NETDEV_BOND_FAIL_OVER_MAC ; 
 int /*<<< orphan*/  NETDEV_BOND_LACP_RATE ; 
 int /*<<< orphan*/  NETDEV_BOND_MODE ; 
 int /*<<< orphan*/  NETDEV_BOND_PRIMARY_RESELECT ; 
 int /*<<< orphan*/  NETDEV_BOND_XMIT_HASH_POLICY ; 
 int /*<<< orphan*/  NETDEV_IP6_TNL_MODE ; 
 int /*<<< orphan*/  NETDEV_IPVLAN_FLAGS ; 
 int /*<<< orphan*/  NETDEV_IPVLAN_MODE ; 
 int /*<<< orphan*/  NETDEV_KIND ; 
 int /*<<< orphan*/  NETDEV_MACVLAN_MODE ; 
 int /*<<< orphan*/  NL_UNION_LINK_INFO_DATA ; 
 int /*<<< orphan*/  RADV_PREFIX_DELEGATION ; 
 int /*<<< orphan*/  SD_LLDP_EVENT ; 
 int /*<<< orphan*/  SD_NDISC_EVENT ; 
 int /*<<< orphan*/  WOL ; 
 int /*<<< orphan*/  address_family ; 
 int /*<<< orphan*/  bond_ad_select ; 
 int /*<<< orphan*/  bond_arp_all_targets ; 
 int /*<<< orphan*/  bond_arp_validate ; 
 int /*<<< orphan*/  bond_fail_over_mac ; 
 int /*<<< orphan*/  bond_lacp_rate ; 
 int /*<<< orphan*/  bond_mode ; 
 int /*<<< orphan*/  bond_primary_reselect ; 
 int /*<<< orphan*/  bond_xmit_hash_policy ; 
 int /*<<< orphan*/  dhcp6_message_status ; 
 int /*<<< orphan*/  dhcp6_message_type ; 
 int /*<<< orphan*/  dhcp_use_domains ; 
 int /*<<< orphan*/  duplex ; 
 int /*<<< orphan*/  ip6tnl_mode ; 
 int /*<<< orphan*/  ipv6_privacy_extensions ; 
 int /*<<< orphan*/  ipvlan_flags ; 
 int /*<<< orphan*/  ipvlan_mode ; 
 int /*<<< orphan*/  link_operstate ; 
 int /*<<< orphan*/  lldp_event ; 
 int /*<<< orphan*/  lldp_mode ; 
 int /*<<< orphan*/  macvlan_mode ; 
 int /*<<< orphan*/  ndisc_event ; 
 int /*<<< orphan*/  netdev_kind ; 
 int /*<<< orphan*/  nl_union_link_info_data ; 
 int /*<<< orphan*/  radv_prefix_delegation ; 
 int /*<<< orphan*/  test_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_table_sparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wol ; 

int main(int argc, char **argv) {
        test_table(bond_ad_select, NETDEV_BOND_AD_SELECT);
        test_table(bond_arp_all_targets, NETDEV_BOND_ARP_ALL_TARGETS);
        test_table(bond_arp_validate, NETDEV_BOND_ARP_VALIDATE);
        test_table(bond_fail_over_mac, NETDEV_BOND_FAIL_OVER_MAC);
        test_table(bond_lacp_rate, NETDEV_BOND_LACP_RATE);
        test_table(bond_mode, NETDEV_BOND_MODE);
        test_table(bond_primary_reselect, NETDEV_BOND_PRIMARY_RESELECT);
        test_table(bond_xmit_hash_policy, NETDEV_BOND_XMIT_HASH_POLICY);
        test_table(dhcp6_message_status, DHCP6_STATUS);
        test_table_sparse(dhcp6_message_type, DHCP6_MESSAGE); /* enum starts from 1 */
        test_table(dhcp_use_domains, DHCP_USE_DOMAINS);
        test_table(duplex, DUP);
        test_table(ip6tnl_mode, NETDEV_IP6_TNL_MODE);
        test_table(ipv6_privacy_extensions, IPV6_PRIVACY_EXTENSIONS);
        test_table(ipvlan_flags, NETDEV_IPVLAN_FLAGS);
        test_table(link_operstate, LINK_OPERSTATE);
        /* test_table(link_state, LINK_STATE);  — not a reversible mapping */
        test_table(lldp_mode, LLDP_MODE);
        test_table(netdev_kind, NETDEV_KIND);
        test_table(nl_union_link_info_data, NL_UNION_LINK_INFO_DATA);
        test_table(radv_prefix_delegation, RADV_PREFIX_DELEGATION);
        test_table(wol, WOL);
        test_table(lldp_event, SD_LLDP_EVENT);
        test_table(ndisc_event, SD_NDISC_EVENT);

        test_table_sparse(ipvlan_mode, NETDEV_IPVLAN_MODE);
        test_table_sparse(macvlan_mode, NETDEV_MACVLAN_MODE);
        test_table_sparse(address_family, ADDRESS_FAMILY);

        return EXIT_SUCCESS;
}