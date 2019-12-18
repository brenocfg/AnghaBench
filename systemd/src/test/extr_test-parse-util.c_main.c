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
 int /*<<< orphan*/  test_parse_boolean () ; 
 int /*<<< orphan*/  test_parse_dev () ; 
 int /*<<< orphan*/  test_parse_errno () ; 
 int /*<<< orphan*/  test_parse_mode () ; 
 int /*<<< orphan*/  test_parse_mtu () ; 
 int /*<<< orphan*/  test_parse_nice () ; 
 int /*<<< orphan*/  test_parse_percent () ; 
 int /*<<< orphan*/  test_parse_percent_unbounded () ; 
 int /*<<< orphan*/  test_parse_permille () ; 
 int /*<<< orphan*/  test_parse_permille_unbounded () ; 
 int /*<<< orphan*/  test_parse_pid () ; 
 int /*<<< orphan*/  test_parse_range () ; 
 int /*<<< orphan*/  test_parse_size () ; 
 int /*<<< orphan*/  test_parse_syscall_and_errno () ; 
 int /*<<< orphan*/  test_safe_atod () ; 
 int /*<<< orphan*/  test_safe_atoi16 () ; 
 int /*<<< orphan*/  test_safe_atoi64 () ; 
 int /*<<< orphan*/  test_safe_atolli () ; 
 int /*<<< orphan*/  test_safe_atou16 () ; 
 int /*<<< orphan*/  test_safe_atou64 () ; 
 int /*<<< orphan*/  test_safe_atoux16 () ; 

int main(int argc, char *argv[]) {
        log_parse_environment();
        log_open();

        test_parse_boolean();
        test_parse_pid();
        test_parse_mode();
        test_parse_size();
        test_parse_range();
        test_safe_atolli();
        test_safe_atou16();
        test_safe_atoi16();
        test_safe_atoux16();
        test_safe_atou64();
        test_safe_atoi64();
        test_safe_atod();
        test_parse_percent();
        test_parse_percent_unbounded();
        test_parse_permille();
        test_parse_permille_unbounded();
        test_parse_nice();
        test_parse_dev();
        test_parse_errno();
        test_parse_syscall_and_errno();
        test_parse_mtu();

        return 0;
}