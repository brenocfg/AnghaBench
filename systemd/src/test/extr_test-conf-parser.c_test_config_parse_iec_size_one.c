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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ config_parse_iec_size (char*,char*,int,char*,int,char*,int /*<<< orphan*/ ,char const*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_config_parse_iec_size_one(const char *rvalue, size_t expected) {
        size_t iec_size = 0;

        assert_se(config_parse_iec_size("unit", "filename", 1, "section", 1, "lvalue", 0, rvalue, &iec_size, NULL) >= 0);
        assert_se(expected == iec_size);
}