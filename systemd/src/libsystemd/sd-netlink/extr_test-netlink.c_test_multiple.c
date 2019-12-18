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
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ sd_netlink_open (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sd_netlink_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_multiple(void) {
        sd_netlink *rtnl1, *rtnl2;

        assert_se(sd_netlink_open(&rtnl1) >= 0);
        assert_se(sd_netlink_open(&rtnl2) >= 0);

        rtnl1 = sd_netlink_unref(rtnl1);
        rtnl2 = sd_netlink_unref(rtnl2);
}