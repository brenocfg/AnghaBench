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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  sd_dhcp_lease ;
typedef  int /*<<< orphan*/  sd_dhcp_client ;

/* Variables and functions */
 int IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_DHCP_CLIENT_EVENT_IP_ACQUIRE ; 
 int /*<<< orphan*/  SD_DHCP_CLIENT_EVENT_SELECTING ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sd_dhcp_client_get_lease (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_dhcp_lease_get_address (int /*<<< orphan*/ *,struct in_addr*) ; 
 scalar_t__ sd_dhcp_lease_get_netmask (int /*<<< orphan*/ *,struct in_addr*) ; 
 int sd_dhcp_lease_get_router (int /*<<< orphan*/ *,struct in_addr const**) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_addr_acq_ack ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int test_addr_acq_acquired(sd_dhcp_client *client, int event,
                                   void *userdata) {
        sd_event *e = userdata;
        sd_dhcp_lease *lease;
        struct in_addr addr;
        const struct in_addr *addrs;

        assert_se(client);
        assert_se(IN_SET(event, SD_DHCP_CLIENT_EVENT_IP_ACQUIRE, SD_DHCP_CLIENT_EVENT_SELECTING));

        assert_se(sd_dhcp_client_get_lease(client, &lease) >= 0);
        assert_se(lease);

        assert_se(sd_dhcp_lease_get_address(lease, &addr) >= 0);
        assert_se(memcmp(&addr.s_addr, &test_addr_acq_ack[44],
                      sizeof(addr.s_addr)) == 0);

        assert_se(sd_dhcp_lease_get_netmask(lease, &addr) >= 0);
        assert_se(memcmp(&addr.s_addr, &test_addr_acq_ack[285],
                      sizeof(addr.s_addr)) == 0);

        assert_se(sd_dhcp_lease_get_router(lease, &addrs) == 1);
        assert_se(memcmp(&addrs[0].s_addr, &test_addr_acq_ack[308],
                         sizeof(addrs[0].s_addr)) == 0);

        if (verbose)
                printf("  DHCP address acquired\n");

        sd_event_exit(e, 0);

        return 0;
}