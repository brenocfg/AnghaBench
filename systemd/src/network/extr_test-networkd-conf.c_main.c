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
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  test_config_parse_address () ; 
 int /*<<< orphan*/  test_config_parse_duid_rawdata () ; 
 int /*<<< orphan*/  test_config_parse_duid_type () ; 
 int /*<<< orphan*/  test_config_parse_hwaddr () ; 
 int /*<<< orphan*/  test_config_parse_match_ifnames () ; 
 int /*<<< orphan*/  test_config_parse_match_strv () ; 

int main(int argc, char **argv) {
        log_parse_environment();
        log_open();

        test_config_parse_duid_type();
        test_config_parse_duid_rawdata();
        test_config_parse_hwaddr();
        test_config_parse_address();
        test_config_parse_match_ifnames();
        test_config_parse_match_strv();

        return 0;
}