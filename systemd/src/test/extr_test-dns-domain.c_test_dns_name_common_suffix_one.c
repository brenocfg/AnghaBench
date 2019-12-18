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
 scalar_t__ dns_name_common_suffix (char const*,char const*,char const**) ; 
 int /*<<< orphan*/  log_info (char*,char const*,char const*,char const*) ; 
 int streq (char const*,char const*) ; 

__attribute__((used)) static void test_dns_name_common_suffix_one(const char *a, const char *b, const char *result) {
        const char *c;

        log_info("%s, %s, →%s", a, b, result);

        assert_se(dns_name_common_suffix(a, b, &c) >= 0);
        assert_se(streq(c, result));
}