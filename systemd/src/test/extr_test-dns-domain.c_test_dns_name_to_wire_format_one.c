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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int dns_name_to_wire_format (char const*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  log_info (char*,char const*,char const*,size_t,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void test_dns_name_to_wire_format_one(const char *what, const char *expect, size_t buffer_sz, int ret) {
        uint8_t buffer[buffer_sz];
        int r;

        log_info("%s, %s, %zu, →%d", what, expect, buffer_sz, ret);

        r = dns_name_to_wire_format(what, buffer, buffer_sz, false);
        assert_se(r == ret);

        if (r < 0)
                return;

        assert_se(!memcmp(buffer, expect, r));
}