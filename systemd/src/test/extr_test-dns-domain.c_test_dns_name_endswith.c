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
 int /*<<< orphan*/  test_dns_name_endswith_one (char*,char*,int) ; 

__attribute__((used)) static void test_dns_name_endswith(void) {
        test_dns_name_endswith_one("", "", true);
        test_dns_name_endswith_one("", "xxx", false);
        test_dns_name_endswith_one("xxx", "", true);
        test_dns_name_endswith_one("x", "x", true);
        test_dns_name_endswith_one("x", "y", false);
        test_dns_name_endswith_one("x.y", "y", true);
        test_dns_name_endswith_one("x.y", "Y", true);
        test_dns_name_endswith_one("x.y", "x", false);
        test_dns_name_endswith_one("x.y.z", "Z", true);
        test_dns_name_endswith_one("x.y.z", "y.Z", true);
        test_dns_name_endswith_one("x.y.z", "x.y.Z", true);
        test_dns_name_endswith_one("x.y.z", "waldo", false);
        test_dns_name_endswith_one("x.y.z.u.v.w", "y.z", false);
        test_dns_name_endswith_one("x.y.z.u.v.w", "u.v.w", true);
        test_dns_name_endswith_one("x.y\001.z", "waldo", -EINVAL);
}