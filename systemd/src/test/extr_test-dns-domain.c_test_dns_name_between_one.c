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
 int dns_name_between (char const*,char const*,char const*) ; 
 scalar_t__ dns_name_equal (char const*,char const*) ; 

__attribute__((used)) static void test_dns_name_between_one(const char *a, const char *b, const char *c, int ret) {
        int r;

        r = dns_name_between(a, b, c);
        assert_se(r == ret);

        r = dns_name_between(c, b, a);
        if (ret >= 0)
                assert_se(r == 0 || dns_name_equal(a, c) > 0);
        else
                assert_se(r == ret);
}