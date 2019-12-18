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

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int hostname_is_valid (char*,int) ; 

__attribute__((used)) static void test_hostname_is_valid(void) {
        assert_se(hostname_is_valid("foobar", false));
        assert_se(hostname_is_valid("foobar.com", false));
        assert_se(!hostname_is_valid("foobar.com.", false));
        assert_se(hostname_is_valid("fooBAR", false));
        assert_se(hostname_is_valid("fooBAR.com", false));
        assert_se(!hostname_is_valid("fooBAR.", false));
        assert_se(!hostname_is_valid("fooBAR.com.", false));
        assert_se(!hostname_is_valid("fööbar", false));
        assert_se(!hostname_is_valid("", false));
        assert_se(!hostname_is_valid(".", false));
        assert_se(!hostname_is_valid("..", false));
        assert_se(!hostname_is_valid("foobar.", false));
        assert_se(!hostname_is_valid(".foobar", false));
        assert_se(!hostname_is_valid("foo..bar", false));
        assert_se(!hostname_is_valid("foo.bar..", false));
        assert_se(!hostname_is_valid("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", false));
        assert_se(!hostname_is_valid("au-xph5-rvgrdsb5hcxc-47et3a5vvkrc-server-wyoz4elpdpe3.openstack.local", false));

        assert_se(hostname_is_valid("foobar", true));
        assert_se(hostname_is_valid("foobar.com", true));
        assert_se(hostname_is_valid("foobar.com.", true));
        assert_se(hostname_is_valid("fooBAR", true));
        assert_se(hostname_is_valid("fooBAR.com", true));
        assert_se(!hostname_is_valid("fooBAR.", true));
        assert_se(hostname_is_valid("fooBAR.com.", true));
        assert_se(!hostname_is_valid("fööbar", true));
        assert_se(!hostname_is_valid("", true));
        assert_se(!hostname_is_valid(".", true));
        assert_se(!hostname_is_valid("..", true));
        assert_se(!hostname_is_valid("foobar.", true));
        assert_se(!hostname_is_valid(".foobar", true));
        assert_se(!hostname_is_valid("foo..bar", true));
        assert_se(!hostname_is_valid("foo.bar..", true));
        assert_se(!hostname_is_valid("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", true));
}