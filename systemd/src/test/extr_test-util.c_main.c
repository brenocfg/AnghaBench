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
 int /*<<< orphan*/  test_align_power2 () ; 
 int /*<<< orphan*/  test_container_of () ; 
 int /*<<< orphan*/  test_div_round_up () ; 
 int /*<<< orphan*/  test_eqzero () ; 
 int /*<<< orphan*/  test_in_set () ; 
 int /*<<< orphan*/  test_log2i () ; 
 int /*<<< orphan*/  test_max () ; 
 int /*<<< orphan*/  test_physical_memory () ; 
 int /*<<< orphan*/  test_physical_memory_scale () ; 
 int /*<<< orphan*/  test_protect_errno () ; 
 int /*<<< orphan*/  test_raw_clone () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_system_tasks_max () ; 
 int /*<<< orphan*/  test_system_tasks_max_scale () ; 
 int /*<<< orphan*/  test_u64log2 () ; 
 int /*<<< orphan*/  test_unprotect_errno () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_INFO);

        test_align_power2();
        test_max();
        test_container_of();
        test_div_round_up();
        test_u64log2();
        test_protect_errno();
        test_unprotect_errno();
        test_in_set();
        test_log2i();
        test_eqzero();
        test_raw_clone();
        test_physical_memory();
        test_physical_memory_scale();
        test_system_tasks_max();
        test_system_tasks_max_scale();

        return 0;
}