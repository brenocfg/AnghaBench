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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int EPERM ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 scalar_t__ RTM_GETLINK ; 
 scalar_t__ RTM_NEWLINK ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ if_nametoindex (char*) ; 
 int sd_netlink_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_netlink_message_get_type (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_netlink_message_read_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/ * sd_netlink_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_netlink_open (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sd_netlink_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_rtnl_message_new_link (int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__,int) ; 
 int /*<<< orphan*/  test_address_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_array () ; 
 int /*<<< orphan*/  test_async (int) ; 
 int /*<<< orphan*/  test_async_destroy_callback (int) ; 
 int /*<<< orphan*/  test_container (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_event_loop (int) ; 
 int /*<<< orphan*/  test_get_addresses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_link_configure (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_link_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_match () ; 
 int /*<<< orphan*/  test_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_message_link_bridge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_multiple () ; 
 int /*<<< orphan*/  test_pipe (int) ; 
 int /*<<< orphan*/  test_route (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_slot_set (int) ; 

int main(void) {
        sd_netlink *rtnl;
        sd_netlink_message *m;
        sd_netlink_message *r;
        const char *string_data;
        int if_loopback;
        uint16_t type;

        test_match();
        test_multiple();

        assert_se(sd_netlink_open(&rtnl) >= 0);
        assert_se(rtnl);

        test_route(rtnl);
        test_message(rtnl);
        test_container(rtnl);
        test_array();

        if_loopback = (int) if_nametoindex("lo");
        assert_se(if_loopback > 0);

        test_async(if_loopback);
        test_slot_set(if_loopback);
        test_async_destroy_callback(if_loopback);
        test_pipe(if_loopback);
        test_event_loop(if_loopback);
        test_link_configure(rtnl, if_loopback);

        test_get_addresses(rtnl);
        test_message_link_bridge(rtnl);

        assert_se(sd_rtnl_message_new_link(rtnl, &m, RTM_GETLINK, if_loopback) >= 0);
        assert_se(m);

        assert_se(sd_netlink_message_get_type(m, &type) >= 0);
        assert_se(type == RTM_GETLINK);

        assert_se(sd_netlink_message_read_string(m, IFLA_IFNAME, &string_data) == -EPERM);

        assert_se(sd_netlink_call(rtnl, m, 0, &r) == 1);
        assert_se(sd_netlink_message_get_type(r, &type) >= 0);
        assert_se(type == RTM_NEWLINK);

        assert_se((r = sd_netlink_message_unref(r)) == NULL);

        assert_se(sd_netlink_call(rtnl, m, -1, &r) == -EPERM);
        assert_se((m = sd_netlink_message_unref(m)) == NULL);
        assert_se((r = sd_netlink_message_unref(r)) == NULL);

        test_link_get(rtnl, if_loopback);
        test_address_get(rtnl, if_loopback);

        assert_se((m = sd_netlink_message_unref(m)) == NULL);
        assert_se((r = sd_netlink_message_unref(r)) == NULL);
        assert_se((rtnl = sd_netlink_unref(rtnl)) == NULL);

        return EXIT_SUCCESS;
}