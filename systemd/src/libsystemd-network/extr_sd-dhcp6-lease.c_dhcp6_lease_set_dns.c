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
struct TYPE_7__ {int dns_count; int /*<<< orphan*/  dns_allocated; int /*<<< orphan*/  dns; } ;
typedef  TYPE_1__ uint8_t ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client ; 
 int dhcp6_option_parse_ip6addrs (TYPE_1__*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int log_dhcp6_client_errno (int /*<<< orphan*/ ,int,char*) ; 

int dhcp6_lease_set_dns(sd_dhcp6_lease *lease, uint8_t *optval, size_t optlen) {
        int r;

        assert_return(lease, -EINVAL);
        assert_return(optval, -EINVAL);

        if (!optlen)
                return 0;

        r = dhcp6_option_parse_ip6addrs(optval, optlen, &lease->dns,
                                        lease->dns_count,
                                        &lease->dns_allocated);
        if (r < 0)
                return log_dhcp6_client_errno(client, r, "Invalid DNS server option: %m");

        lease->dns_count = r;

        return 0;
}