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
 int dns_name_is_valid (char const*) ; 
 int dns_name_is_valid_ldh (char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,int) ; 

__attribute__((used)) static void test_dns_name_is_valid_one(const char *s, int ret, int ret_ldh) {
        log_info("%s, →%d", s, ret);

        assert_se(dns_name_is_valid(s) == ret);
        assert_se(dns_name_is_valid_ldh(s) == ret_ldh);
}