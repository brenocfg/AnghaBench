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
 int /*<<< orphan*/  EUCLEAN ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int _LOG_TARGET_MAX ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_set_target (int) ; 
 int /*<<< orphan*/  test_file () ; 
 int /*<<< orphan*/  test_log_struct () ; 
 int /*<<< orphan*/  test_log_syntax () ; 
 int /*<<< orphan*/  test_long_lines () ; 

int main(int argc, char* argv[]) {
        int target;

        test_file();

        for (target = 0; target < _LOG_TARGET_MAX; target++) {
                log_set_target(target);
                log_open();

                test_log_struct();
                test_long_lines();
                test_log_syntax();
        }

        assert_se(log_info_errno(SYNTHETIC_ERRNO(EUCLEAN), "foo") == -EUCLEAN);

        return 0;
}