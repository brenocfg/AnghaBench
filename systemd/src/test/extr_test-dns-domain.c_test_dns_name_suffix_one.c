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
 int dns_name_suffix (char const*,unsigned int,char const**) ; 
 int /*<<< orphan*/  log_info (char*,char const*,unsigned int,char const*,int) ; 
 int streq_ptr (char const*,char const*) ; 

__attribute__((used)) static void test_dns_name_suffix_one(const char *name, unsigned n_labels, const char *result, int ret) {
        const char *p = NULL;

        log_info("%s, %d, →%s, %d", name, n_labels, result, ret);

        assert_se(ret == dns_name_suffix(name, n_labels, &p));
        assert_se(streq_ptr(p, result));
}