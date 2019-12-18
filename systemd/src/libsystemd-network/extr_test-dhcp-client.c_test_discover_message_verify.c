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
struct DHCPMessage {int /*<<< orphan*/  xid; } ;

/* Variables and functions */
 int DHCP_DISCOVER ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_options ; 
 int dhcp_option_parse (struct DHCPMessage*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int test_discover_message_verify(size_t size, struct DHCPMessage *dhcp) {
        int res;

        res = dhcp_option_parse(dhcp, size, check_options, NULL, NULL);
        assert_se(res == DHCP_DISCOVER);

        if (verbose)
                printf("  recv DHCP Discover 0x%08x\n", be32toh(dhcp->xid));

        return 0;
}