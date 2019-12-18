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
 int /*<<< orphan*/  test_dns_name_concat_one (char*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_dns_name_concat(void) {
        test_dns_name_concat_one("", "", 0, ".");
        test_dns_name_concat_one(".", "", 0, ".");
        test_dns_name_concat_one("", ".", 0, ".");
        test_dns_name_concat_one(".", ".", 0, ".");
        test_dns_name_concat_one("foo", "bar", 0, "foo.bar");
        test_dns_name_concat_one("foo.foo", "bar.bar", 0, "foo.foo.bar.bar");
        test_dns_name_concat_one("foo", NULL, 0, "foo");
        test_dns_name_concat_one("foo", ".", 0, "foo");
        test_dns_name_concat_one("foo.", "bar.", 0, "foo.bar");
        test_dns_name_concat_one(NULL, NULL, 0, ".");
        test_dns_name_concat_one(NULL, ".", 0, ".");
        test_dns_name_concat_one(NULL, "foo", 0, "foo");
}