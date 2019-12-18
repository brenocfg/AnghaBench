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
struct in_addr {int s_addr; } ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_INFO_DATA ; 
 int /*<<< orphan*/  IFLA_IPTUN_LOCAL ; 
 int /*<<< orphan*/  IFLA_IPTUN_PROTO ; 
 int /*<<< orphan*/  IFLA_IPTUN_REMOTE ; 
 int /*<<< orphan*/  IFLA_LINKINFO ; 
 int /*<<< orphan*/  IFLA_MTU ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int*) ; 
 int load_module (char*) ; 
 int log_tests_skipped (char*) ; 
 int log_tests_skipped_errno (int,char*) ; 
 int sd_netlink_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_netlink_message_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sd_netlink_message_append_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sd_netlink_message_append_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_netlink_message_close_container (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_netlink_message_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_netlink_message_open_container_union (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sd_netlink_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_rtnl_message_new_link (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_tunnel_configure(sd_netlink *rtnl) {
        int r;
        sd_netlink_message *m, *n;
        struct in_addr local, remote;

        /* skip test if module cannot be loaded */
        r = load_module("ipip");
        if (r < 0)
                return log_tests_skipped_errno(r, "failed to load module 'ipip'");

        r = load_module("sit");
        if (r < 0)
                return log_tests_skipped_errno(r, "failed to load module 'sit'");

        if (getuid() != 0)
                return log_tests_skipped("not root");

        /* IPIP tunnel */
        assert_se(sd_rtnl_message_new_link(rtnl, &m, RTM_NEWLINK, 0) >= 0);
        assert_se(m);

        assert_se(sd_netlink_message_append_string(m, IFLA_IFNAME, "ipip-tunnel") >= 0);
        assert_se(sd_netlink_message_append_u32(m, IFLA_MTU, 1234)>= 0);

        assert_se(sd_netlink_message_open_container(m, IFLA_LINKINFO) >= 0);

        assert_se(sd_netlink_message_open_container_union(m, IFLA_INFO_DATA, "ipip") >= 0);

        inet_pton(AF_INET, "192.168.21.1", &local.s_addr);
        assert_se(sd_netlink_message_append_u32(m, IFLA_IPTUN_LOCAL, local.s_addr) >= 0);

        inet_pton(AF_INET, "192.168.21.2", &remote.s_addr);
        assert_se(sd_netlink_message_append_u32(m, IFLA_IPTUN_REMOTE, remote.s_addr) >= 0);

        assert_se(sd_netlink_message_close_container(m) >= 0);
        assert_se(sd_netlink_message_close_container(m) >= 0);

        assert_se(sd_netlink_call(rtnl, m, -1, 0) == 1);

        assert_se((m = sd_netlink_message_unref(m)) == NULL);

        /* sit */
        assert_se(sd_rtnl_message_new_link(rtnl, &n, RTM_NEWLINK, 0) >= 0);
        assert_se(n);

        assert_se(sd_netlink_message_append_string(n, IFLA_IFNAME, "sit-tunnel") >= 0);
        assert_se(sd_netlink_message_append_u32(n, IFLA_MTU, 1234)>= 0);

        assert_se(sd_netlink_message_open_container(n, IFLA_LINKINFO) >= 0);

        assert_se(sd_netlink_message_open_container_union(n, IFLA_INFO_DATA, "sit") >= 0);

        assert_se(sd_netlink_message_append_u8(n, IFLA_IPTUN_PROTO, IPPROTO_IPIP) >= 0);

        inet_pton(AF_INET, "192.168.21.3", &local.s_addr);
        assert_se(sd_netlink_message_append_u32(n, IFLA_IPTUN_LOCAL, local.s_addr) >= 0);

        inet_pton(AF_INET, "192.168.21.4", &remote.s_addr);
        assert_se(sd_netlink_message_append_u32(n, IFLA_IPTUN_REMOTE, remote.s_addr) >= 0);

        assert_se(sd_netlink_message_close_container(n) >= 0);
        assert_se(sd_netlink_message_close_container(n) >= 0);

        assert_se(sd_netlink_call(rtnl, n, -1, 0) == 1);

        assert_se((n = sd_netlink_message_unref(n)) == NULL);

        return EXIT_SUCCESS;
}