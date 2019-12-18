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
 int /*<<< orphan*/  test_dns_name_normalize_one (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_dns_name_normalize(void) {
        test_dns_name_normalize_one("", ".", 0);
        test_dns_name_normalize_one("f", "f", 0);
        test_dns_name_normalize_one("f.waldi", "f.waldi", 0);
        test_dns_name_normalize_one("f \\032.waldi", "f\\032\\032.waldi", 0);
        test_dns_name_normalize_one("\\000", "\\000", 0);
        test_dns_name_normalize_one("..", NULL, -EINVAL);
        test_dns_name_normalize_one(".foobar", NULL, -EINVAL);
        test_dns_name_normalize_one("foobar.", "foobar", 0);
        test_dns_name_normalize_one(".", ".", 0);
}