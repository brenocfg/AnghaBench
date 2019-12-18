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
 int /*<<< orphan*/  test_dns_name_reverse_one (char*,char*) ; 

__attribute__((used)) static void test_dns_name_reverse(void) {
        test_dns_name_reverse_one("47.11.8.15", "15.8.11.47.in-addr.arpa");
        test_dns_name_reverse_one("fe80::47", "7.4.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.8.e.f.ip6.arpa");
        test_dns_name_reverse_one("127.0.0.1", "1.0.0.127.in-addr.arpa");
        test_dns_name_reverse_one("::1", "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa");
}