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
 scalar_t__ config_parse_log_facility (char*,char*,int,char*,int,char*,int /*<<< orphan*/ ,char const*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_config_parse_log_facility_one(const char *rvalue, int expected) {
        int log_facility = 0;

        assert_se(config_parse_log_facility("unit", "filename", 1, "section", 1, "lvalue", 0, rvalue, &log_facility, NULL) >= 0);
        assert_se(expected == log_facility);
}