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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int config_parse_hwaddr (char*,char*,int,char*,int,char*,int /*<<< orphan*/ ,char const*,struct ether_addr**,int /*<<< orphan*/ *) ; 
 struct ether_addr* ether_addr_equal (struct ether_addr const*,struct ether_addr*) ; 
 int /*<<< orphan*/  free (struct ether_addr*) ; 

__attribute__((used)) static void test_config_parse_hwaddr_one(const char *rvalue, int ret, const struct ether_addr* expected) {
        struct ether_addr *actual = NULL;
        int r;

        r = config_parse_hwaddr("network", "filename", 1, "section", 1, "lvalue", 0, rvalue, &actual, NULL);
        assert_se(ret == r);
        if (expected) {
                assert_se(actual);
                assert_se(ether_addr_equal(expected, actual));
        } else
                assert_se(actual == NULL);

        free(actual);
}