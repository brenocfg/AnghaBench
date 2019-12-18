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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  test_config_parse_log_level_one (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_parse_log_level(void) {
        test_config_parse_log_level_one("debug", LOG_DEBUG);
        test_config_parse_log_level_one("info", LOG_INFO);

        test_config_parse_log_level_one("garbage", 0);
}