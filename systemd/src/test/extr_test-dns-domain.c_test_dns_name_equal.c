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
 int EINVAL ; 
 int /*<<< orphan*/  test_dns_name_equal_one (char*,char*,int) ; 

__attribute__((used)) static void test_dns_name_equal(void) {
        test_dns_name_equal_one("", "", true);
        test_dns_name_equal_one("x", "x", true);
        test_dns_name_equal_one("x", "x.", true);
        test_dns_name_equal_one("abc.def", "abc.def", true);
        test_dns_name_equal_one("abc.def", "ABC.def", true);
        test_dns_name_equal_one("abc.def", "CBA.def", false);
        test_dns_name_equal_one("", "xxx", false);
        test_dns_name_equal_one("ab", "a", false);
        test_dns_name_equal_one("\\000", "\\000", true);
        test_dns_name_equal_one(".", "", true);
        test_dns_name_equal_one(".", ".", true);
        test_dns_name_equal_one("..", "..", -EINVAL);
}