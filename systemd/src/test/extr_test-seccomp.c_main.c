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
 int /*<<< orphan*/  test_architecture_table () ; 
 int /*<<< orphan*/  test_filter_sets () ; 
 int /*<<< orphan*/  test_filter_sets_ordered () ; 
 int /*<<< orphan*/  test_load_syscall_filter_set_raw () ; 
 int /*<<< orphan*/  test_lock_personality () ; 
 int /*<<< orphan*/  test_memory_deny_write_execute_mmap () ; 
 int /*<<< orphan*/  test_memory_deny_write_execute_shmat () ; 
 int /*<<< orphan*/  test_protect_sysctl () ; 
 int /*<<< orphan*/  test_protect_syslog () ; 
 int /*<<< orphan*/  test_restrict_address_families () ; 
 int /*<<< orphan*/  test_restrict_archs () ; 
 int /*<<< orphan*/  test_restrict_namespace () ; 
 int /*<<< orphan*/  test_restrict_realtime () ; 
 int /*<<< orphan*/  test_restrict_suid_sgid () ; 
 int /*<<< orphan*/  test_seccomp_arch_to_string () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_syscall_filter_set_find () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_seccomp_arch_to_string();
        test_architecture_table();
        test_syscall_filter_set_find();
        test_filter_sets();
        test_filter_sets_ordered();
        test_restrict_namespace();
        test_protect_sysctl();
        test_protect_syslog();
        test_restrict_address_families();
        test_restrict_realtime();
        test_memory_deny_write_execute_mmap();
        test_memory_deny_write_execute_shmat();
        test_restrict_archs();
        test_load_syscall_filter_set_raw();
        test_lock_personality();
        test_restrict_suid_sgid();

        return 0;
}