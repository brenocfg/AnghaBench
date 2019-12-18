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
struct TYPE_7__ {int all_slaves_active; int tlb_dynamic_lb; int /*<<< orphan*/  lp_interval; int /*<<< orphan*/  num_grat_arp; int /*<<< orphan*/  packets_per_slave; int /*<<< orphan*/  resend_igmp; int /*<<< orphan*/  primary_reselect; int /*<<< orphan*/  arp_all_targets; int /*<<< orphan*/  arp_validate; int /*<<< orphan*/  fail_over_mac; int /*<<< orphan*/  ad_select; int /*<<< orphan*/  lacp_rate; int /*<<< orphan*/  xmit_hash_policy; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ Bond ;

/* Variables and functions */
 TYPE_1__* BOND (TYPE_1__*) ; 
 int /*<<< orphan*/  GRATUITOUS_ARP_DEFAULT ; 
 int /*<<< orphan*/  LEARNING_PACKETS_INTERVAL_MIN_SEC ; 
 int /*<<< orphan*/  PACKETS_PER_SLAVE_DEFAULT ; 
 int /*<<< orphan*/  RESEND_IGMP_DEFAULT ; 
 int /*<<< orphan*/  _NETDEV_BOND_AD_SELECT_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_ARP_ALL_TARGETS_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_ARP_VALIDATE_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_FAIL_OVER_MAC_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_LACP_RATE_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_MODE_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_PRIMARY_RESELECT_INVALID ; 
 int /*<<< orphan*/  _NETDEV_BOND_XMIT_HASH_POLICY_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void bond_init(NetDev *netdev) {
        Bond *b;

        assert(netdev);

        b = BOND(netdev);

        assert(b);

        b->mode = _NETDEV_BOND_MODE_INVALID;
        b->xmit_hash_policy = _NETDEV_BOND_XMIT_HASH_POLICY_INVALID;
        b->lacp_rate = _NETDEV_BOND_LACP_RATE_INVALID;
        b->ad_select = _NETDEV_BOND_AD_SELECT_INVALID;
        b->fail_over_mac = _NETDEV_BOND_FAIL_OVER_MAC_INVALID;
        b->arp_validate = _NETDEV_BOND_ARP_VALIDATE_INVALID;
        b->arp_all_targets = _NETDEV_BOND_ARP_ALL_TARGETS_INVALID;
        b->primary_reselect = _NETDEV_BOND_PRIMARY_RESELECT_INVALID;

        b->all_slaves_active = false;
        b->tlb_dynamic_lb = -1;

        b->resend_igmp = RESEND_IGMP_DEFAULT;
        b->packets_per_slave = PACKETS_PER_SLAVE_DEFAULT;
        b->num_grat_arp = GRATUITOUS_ARP_DEFAULT;
        b->lp_interval = LEARNING_PACKETS_INTERVAL_MIN_SEC;
}