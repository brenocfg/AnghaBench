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
 int dns_name_equal_skip (char const*,unsigned int,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,unsigned int,char const*,int) ; 

__attribute__((used)) static void test_dns_name_equal_skip_one(const char *a, unsigned n_labels, const char *b, int ret) {
        log_info("%s, %u, %s, →%d", a, n_labels, b, ret);

        assert_se(dns_name_equal_skip(a, n_labels, b) == ret);
}