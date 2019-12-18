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
 int /*<<< orphan*/  test_config_parse_int_one (char*,int) ; 

__attribute__((used)) static void test_config_parse_int(void) {
        test_config_parse_int_one("1024", 1024);
        test_config_parse_int_one("-1024", -1024);
        test_config_parse_int_one("0", 0);

        test_config_parse_int_one("99999999999999999999999999999999999999999999999999999999", -1);
        test_config_parse_int_one("-99999999999999999999999999999999999999999999999999999999", -1);
        test_config_parse_int_one("1G", -1);
        test_config_parse_int_one("garbage", -1);
}