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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  ambient_capabilities_supported () ; 
 int /*<<< orphan*/  fork_test (int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int log_tests_skipped (char*) ; 
 scalar_t__ setup_tests (int*) ; 
 int /*<<< orphan*/  show_capabilities () ; 
 int /*<<< orphan*/  test_drop_privileges () ; 
 int /*<<< orphan*/  test_ensure_cap_64bit () ; 
 int /*<<< orphan*/  test_have_effective_cap ; 
 int /*<<< orphan*/  test_last_cap_file () ; 
 int /*<<< orphan*/  test_last_cap_probe () ; 
 int /*<<< orphan*/  test_set_ambient_caps ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_update_inherited_set () ; 
 int /*<<< orphan*/  yes_no (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        bool run_ambient;

        test_setup_logging(LOG_INFO);

        test_ensure_cap_64bit();

        test_last_cap_file();
        test_last_cap_probe();

        log_info("have ambient caps: %s", yes_no(ambient_capabilities_supported()));

        if (getuid() != 0)
                return log_tests_skipped("not running as root");

        if (setup_tests(&run_ambient) < 0)
                return log_tests_skipped("setup failed");

        show_capabilities();

        test_drop_privileges();
        test_update_inherited_set();

        fork_test(test_have_effective_cap);

        if (run_ambient)
                fork_test(test_set_ambient_caps);

        return 0;
}