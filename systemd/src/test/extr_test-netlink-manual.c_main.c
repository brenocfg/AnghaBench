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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ sd_netlink_open (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sd_netlink_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int test_tunnel_configure (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
        sd_netlink *rtnl;
        int r;

        test_setup_logging(LOG_INFO);

        assert_se(sd_netlink_open(&rtnl) >= 0);
        assert_se(rtnl);

        r = test_tunnel_configure(rtnl);

        assert_se((rtnl = sd_netlink_unref(rtnl)) == NULL);

        return r;
}