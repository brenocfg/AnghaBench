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
struct in_addr {int dummy; } ;
struct ifa_cacheinfo {int dummy; } ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IFA_ADDRESS ; 
 int /*<<< orphan*/  IFA_CACHEINFO ; 
 int /*<<< orphan*/  IFA_LABEL ; 
 int /*<<< orphan*/  IFA_LOCAL ; 
 int /*<<< orphan*/  RTM_GETADDR ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int sd_netlink_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_netlink_message_read_cache_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifa_cacheinfo*) ; 
 scalar_t__ sd_netlink_message_read_in_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in_addr*) ; 
 scalar_t__ sd_netlink_message_read_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/ * sd_netlink_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_rtnl_message_new_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_address_get(sd_netlink *rtnl, int ifindex) {
        sd_netlink_message *m;
        sd_netlink_message *r;
        struct in_addr in_data;
        struct ifa_cacheinfo cache;
        const char *label;

        assert_se(sd_rtnl_message_new_addr(rtnl, &m, RTM_GETADDR, ifindex, AF_INET) >= 0);
        assert_se(m);

        assert_se(sd_netlink_call(rtnl, m, -1, &r) == 1);

        assert_se(sd_netlink_message_read_in_addr(r, IFA_LOCAL, &in_data) == 0);
        assert_se(sd_netlink_message_read_in_addr(r, IFA_ADDRESS, &in_data) == 0);
        assert_se(sd_netlink_message_read_string(r, IFA_LABEL, &label) == 0);
        assert_se(sd_netlink_message_read_cache_info(r, IFA_CACHEINFO, &cache) == 0);

        assert_se((m = sd_netlink_message_unref(m)) == NULL);
        assert_se((r = sd_netlink_message_unref(r)) == NULL);

}