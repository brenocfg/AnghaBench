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
 int /*<<< orphan*/  print_securities () ; 
 int /*<<< orphan*/  test_condition_test_ac_power () ; 
 int /*<<< orphan*/  test_condition_test_architecture () ; 
 int /*<<< orphan*/  test_condition_test_control_group_controller () ; 
 int /*<<< orphan*/  test_condition_test_cpus () ; 
 int /*<<< orphan*/  test_condition_test_group () ; 
 int /*<<< orphan*/  test_condition_test_host () ; 
 int /*<<< orphan*/  test_condition_test_kernel_command_line () ; 
 int /*<<< orphan*/  test_condition_test_kernel_version () ; 
 int /*<<< orphan*/  test_condition_test_memory () ; 
 int /*<<< orphan*/  test_condition_test_null () ; 
 int /*<<< orphan*/  test_condition_test_path () ; 
 int /*<<< orphan*/  test_condition_test_security () ; 
 int /*<<< orphan*/  test_condition_test_user () ; 
 int /*<<< orphan*/  test_condition_test_virtualization () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_condition_test_path();
        test_condition_test_ac_power();
        test_condition_test_host();
        test_condition_test_architecture();
        test_condition_test_kernel_command_line();
        test_condition_test_kernel_version();
        test_condition_test_null();
        test_condition_test_security();
        print_securities();
        test_condition_test_virtualization();
        test_condition_test_user();
        test_condition_test_group();
        test_condition_test_control_group_controller();
        test_condition_test_cpus();
        test_condition_test_memory();

        return 0;
}