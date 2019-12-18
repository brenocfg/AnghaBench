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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_protocol_from_name (char const*) ; 
 int /*<<< orphan*/  ip_protocol_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_ip_protocol (char const*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_str(const char *s) {
        assert_se(streq(ip_protocol_to_name(ip_protocol_from_name(s)), s));
        assert_se(streq(ip_protocol_to_name(parse_ip_protocol(s)), s));
}