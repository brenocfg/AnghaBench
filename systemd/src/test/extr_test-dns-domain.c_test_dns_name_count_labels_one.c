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
 int dns_name_count_labels (char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,int) ; 

__attribute__((used)) static void test_dns_name_count_labels_one(const char *name, int n) {
        log_info("%s, →%d", name, n);

        assert_se(dns_name_count_labels(name) == n);
}