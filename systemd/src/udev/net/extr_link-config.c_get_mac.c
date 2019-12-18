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
typedef  int /*<<< orphan*/  uint64_t ;
struct ether_addr {int* ether_addr_octet; } ;
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  result ;
typedef  scalar_t__ MACAddressPolicy ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_ADDRESS_POLICY_PERSISTENT ; 
 scalar_t__ MAC_ADDRESS_POLICY_RANDOM ; 
 int /*<<< orphan*/  NAMING_STABLE_VIRTUAL_MACS ; 
#define  NET_ADDR_PERM 131 
#define  NET_ADDR_RANDOM 130 
#define  NET_ADDR_SET 129 
#define  NET_ADDR_STOLEN 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int link_unsigned_attribute (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int log_device_debug (int /*<<< orphan*/ *,char*,...) ; 
 int log_device_warning (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int log_device_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  mac_address_policy_to_string (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  naming_scheme_has (int /*<<< orphan*/ ) ; 
 int net_get_unique_predictable_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_bytes (int*,int) ; 

__attribute__((used)) static int get_mac(sd_device *device, MACAddressPolicy policy, struct ether_addr *mac) {
        unsigned addr_type;
        bool want_random = policy == MAC_ADDRESS_POLICY_RANDOM;
        int r;

        assert(IN_SET(policy, MAC_ADDRESS_POLICY_RANDOM, MAC_ADDRESS_POLICY_PERSISTENT));

        r = link_unsigned_attribute(device, "addr_assign_type", &addr_type);
        if (r < 0)
                return r;
        switch (addr_type) {
        case NET_ADDR_SET:
                return log_device_debug(device, "MAC on the device already set by userspace");
        case NET_ADDR_STOLEN:
                return log_device_debug(device, "MAC on the device already set based on another device");
        case NET_ADDR_RANDOM:
        case NET_ADDR_PERM:
                break;
        default:
                return log_device_warning(device, "Unknown addr_assign_type %u, ignoring", addr_type);
        }

        if (want_random == (addr_type == NET_ADDR_RANDOM))
                return log_device_debug(device, "MAC on the device already matches policy *%s*",
                                        mac_address_policy_to_string(policy));

        if (want_random) {
                log_device_debug(device, "Using random bytes to generate MAC");
                random_bytes(mac->ether_addr_octet, ETH_ALEN);
        } else {
                uint64_t result;

                r = net_get_unique_predictable_data(device,
                                                    naming_scheme_has(NAMING_STABLE_VIRTUAL_MACS),
                                                    &result);
                if (r < 0)
                        return log_device_warning_errno(device, r, "Could not generate persistent MAC: %m");

                log_device_debug(device, "Using generated persistent MAC address");
                assert_cc(ETH_ALEN <= sizeof(result));
                memcpy(mac->ether_addr_octet, &result, ETH_ALEN);
        }

        /* see eth_random_addr in the kernel */
        mac->ether_addr_octet[0] &= 0xfe;  /* clear multicast bit */
        mac->ether_addr_octet[0] |= 0x02;  /* set local assignment bit (IEEE802) */
        return 1;
}