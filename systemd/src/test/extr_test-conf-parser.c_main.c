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
 unsigned int ELEMENTSOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  test_config_parse (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_config_parse_iec_size () ; 
 int /*<<< orphan*/  test_config_parse_iec_uint64 () ; 
 int /*<<< orphan*/  test_config_parse_int () ; 
 int /*<<< orphan*/  test_config_parse_log_facility () ; 
 int /*<<< orphan*/  test_config_parse_log_level () ; 
 int /*<<< orphan*/  test_config_parse_mode () ; 
 int /*<<< orphan*/  test_config_parse_nsec () ; 
 int /*<<< orphan*/  test_config_parse_path () ; 
 int /*<<< orphan*/  test_config_parse_sec () ; 
 int /*<<< orphan*/  test_config_parse_si_size () ; 
 int /*<<< orphan*/  test_config_parse_strv () ; 
 int /*<<< orphan*/  test_config_parse_unsigned () ; 

int main(int argc, char **argv) {
        unsigned i;

        log_parse_environment();
        log_open();

        test_config_parse_path();
        test_config_parse_log_level();
        test_config_parse_log_facility();
        test_config_parse_iec_size();
        test_config_parse_si_size();
        test_config_parse_int();
        test_config_parse_unsigned();
        test_config_parse_strv();
        test_config_parse_mode();
        test_config_parse_sec();
        test_config_parse_nsec();
        test_config_parse_iec_uint64();

        for (i = 0; i < ELEMENTSOF(config_file); i++)
                test_config_parse(i, config_file[i]);

        return 0;
}