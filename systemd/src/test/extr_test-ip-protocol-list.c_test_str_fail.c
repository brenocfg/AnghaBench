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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  ip_protocol_from_name (char const*) ; 
 int /*<<< orphan*/  parse_ip_protocol (char const*) ; 

__attribute__((used)) static void test_str_fail(const char *s) {
        assert_se(ip_protocol_from_name(s) == -EINVAL);
        assert_se(parse_ip_protocol(s) == -EINVAL);
}