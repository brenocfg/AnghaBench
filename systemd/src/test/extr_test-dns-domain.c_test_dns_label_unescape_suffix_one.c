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
 int dns_label_unescape_suffix (char const*,char const**,char*,size_t) ; 
 int /*<<< orphan*/  log_info (char*,char const*,char const*,char const*,size_t,int,int) ; 
 int streq (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_dns_label_unescape_suffix_one(const char *what, const char *expect1, const char *expect2, size_t buffer_sz, int ret1, int ret2) {
        char buffer[buffer_sz];
        const char *label;
        int r;

        log_info("%s, %s, %s, %zu, %d, %d", what, expect1, expect2, buffer_sz, ret1, ret2);

        label = what + strlen(what);

        r = dns_label_unescape_suffix(what, &label, buffer, buffer_sz);
        assert_se(r == ret1);
        if (r >= 0)
                assert_se(streq(buffer, expect1));

        r = dns_label_unescape_suffix(what, &label, buffer, buffer_sz);
        assert_se(r == ret2);
        if (r >= 0)
                assert_se(streq(buffer, expect2));
}