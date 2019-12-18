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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  test_in_addr_prefix_to_string_unoptimized (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_in_addr_prefix_to_string_valid (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_in_addr_prefix_to_string(void) {
        test_in_addr_prefix_to_string_valid(AF_INET, "0.0.0.0/32");
        test_in_addr_prefix_to_string_valid(AF_INET, "1.2.3.4/0");
        test_in_addr_prefix_to_string_valid(AF_INET, "1.2.3.4/24");
        test_in_addr_prefix_to_string_valid(AF_INET, "1.2.3.4/32");
        test_in_addr_prefix_to_string_valid(AF_INET, "255.255.255.255/32");

        test_in_addr_prefix_to_string_valid(AF_INET6, "::1/128");
        test_in_addr_prefix_to_string_valid(AF_INET6, "fd00:abcd::1/64");
        test_in_addr_prefix_to_string_valid(AF_INET6, "fd00:abcd::1234:1/64");
        test_in_addr_prefix_to_string_valid(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888/128");

        test_in_addr_prefix_to_string_unoptimized(AF_INET, "0.0.0.0");
        test_in_addr_prefix_to_string_unoptimized(AF_INET, "192.168.0.1");

        test_in_addr_prefix_to_string_unoptimized(AF_INET6, "fd00:0000:0000:0000:0000:0000:0000:0001/64");
        test_in_addr_prefix_to_string_unoptimized(AF_INET6, "fd00:1111::0000:2222:3333:4444:0001/64");
}