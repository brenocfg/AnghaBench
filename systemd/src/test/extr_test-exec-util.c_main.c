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
 int /*<<< orphan*/  test_environment_gathering () ; 
 int /*<<< orphan*/  test_error_catching () ; 
 int /*<<< orphan*/  test_exec_command_flags_from_strv () ; 
 int /*<<< orphan*/  test_exec_command_flags_to_strv () ; 
 int /*<<< orphan*/  test_execute_directory (int) ; 
 int /*<<< orphan*/  test_execution_order () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_stdout_gathering () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_execute_directory(true);
        test_execute_directory(false);
        test_execution_order();
        test_stdout_gathering();
        test_environment_gathering();
        test_error_catching();
        test_exec_command_flags_from_strv();
        test_exec_command_flags_to_strv();

        return 0;
}