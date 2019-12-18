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
 int /*<<< orphan*/  LOG_MAIL ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  test_config_parse_log_facility_one (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_parse_log_facility(void) {
        test_config_parse_log_facility_one("mail", LOG_MAIL);
        test_config_parse_log_facility_one("user", LOG_USER);

        test_config_parse_log_facility_one("garbage", 0);
}