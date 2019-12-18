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
 int /*<<< orphan*/  test_dns_name_startswith_one (char*,char*,int) ; 

__attribute__((used)) static void test_dns_name_startswith(void) {
        test_dns_name_startswith_one("", "", true);
        test_dns_name_startswith_one("", "xxx", false);
        test_dns_name_startswith_one("xxx", "", true);
        test_dns_name_startswith_one("x", "x", true);
        test_dns_name_startswith_one("x", "y", false);
        test_dns_name_startswith_one("x.y", "x.y", true);
        test_dns_name_startswith_one("x.y", "y.x", false);
        test_dns_name_startswith_one("x.y", "x", true);
        test_dns_name_startswith_one("x.y", "X", true);
        test_dns_name_startswith_one("x.y", "y", false);
        test_dns_name_startswith_one("x.y", "", true);
        test_dns_name_startswith_one("x.y", "X", true);
}