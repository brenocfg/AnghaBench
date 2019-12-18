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
struct rlimit {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACTION_RUN ; 
 scalar_t__ NSEC_INFINITY ; 
 int /*<<< orphan*/  PR_SET_CHILD_SUBREAPER ; 
 int /*<<< orphan*/  PR_SET_NO_NEW_PRIVS ; 
 int /*<<< orphan*/  PR_SET_TIMERSLACK ; 
 scalar_t__ arg_action ; 
 int /*<<< orphan*/  arg_capability_bounding_set ; 
 int /*<<< orphan*/  arg_machine_id ; 
 scalar_t__ arg_no_new_privs ; 
 int /*<<< orphan*/  arg_runtime_watchdog ; 
 scalar_t__ arg_syscall_archs ; 
 scalar_t__ arg_system ; 
 scalar_t__ arg_timer_slack_nsec ; 
 scalar_t__ arg_watchdog_device ; 
 int /*<<< orphan*/  assert (char const**) ; 
 int /*<<< orphan*/  bump_file_max_and_nr_open () ; 
 int /*<<< orphan*/  bump_rlimit_memlock (struct rlimit*) ; 
 int /*<<< orphan*/  bump_rlimit_nofile (struct rlimit*) ; 
 int /*<<< orphan*/  bump_unix_max_dgram_qlen () ; 
 int /*<<< orphan*/  cap_test_all (int /*<<< orphan*/ ) ; 
 int capability_bounding_set_drop (int /*<<< orphan*/ ,int) ; 
 int capability_bounding_set_drop_usermode (int /*<<< orphan*/ ) ; 
 int enforce_syscall_archs (scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  hostname_setup () ; 
 int /*<<< orphan*/  install_crash_handler () ; 
 int log_emergency_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,...) ; 
 int /*<<< orphan*/  loopback_setup () ; 
 int /*<<< orphan*/  machine_id_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mount_cgroup_controllers () ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  status_welcome () ; 
 int /*<<< orphan*/  test_usr () ; 
 scalar_t__ timestamp_is_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cpu_affinity (int) ; 
 int /*<<< orphan*/  update_numa_policy (int) ; 
 int watchdog_set_device (scalar_t__) ; 
 int /*<<< orphan*/  watchdog_set_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_container_id () ; 

__attribute__((used)) static int initialize_runtime(
                bool skip_setup,
                struct rlimit *saved_rlimit_nofile,
                struct rlimit *saved_rlimit_memlock,
                const char **ret_error_message) {
        int r;

        assert(ret_error_message);

        /* Sets up various runtime parameters. Many of these initializations are conditionalized:
         *
         * - Some only apply to --system instances
         * - Some only apply to --user instances
         * - Some only apply when we first start up, but not when we reexecute
         */

        if (arg_action != ACTION_RUN)
                return 0;

        update_cpu_affinity(skip_setup);
        update_numa_policy(skip_setup);

        if (arg_system) {
                /* Make sure we leave a core dump without panicking the kernel. */
                install_crash_handler();

                if (!skip_setup) {
                        r = mount_cgroup_controllers();
                        if (r < 0) {
                                *ret_error_message = "Failed to mount cgroup hierarchies";
                                return r;
                        }

                        status_welcome();
                        hostname_setup();
                        machine_id_setup(NULL, arg_machine_id, NULL);
                        loopback_setup();
                        bump_unix_max_dgram_qlen();
                        bump_file_max_and_nr_open();
                        test_usr();
                        write_container_id();
                }

                if (arg_watchdog_device) {
                        r = watchdog_set_device(arg_watchdog_device);
                        if (r < 0)
                                log_warning_errno(r, "Failed to set watchdog device to %s, ignoring: %m", arg_watchdog_device);
                }

                if (timestamp_is_set(arg_runtime_watchdog))
                        watchdog_set_timeout(&arg_runtime_watchdog);
        }

        if (arg_timer_slack_nsec != NSEC_INFINITY)
                if (prctl(PR_SET_TIMERSLACK, arg_timer_slack_nsec) < 0)
                        log_warning_errno(errno, "Failed to adjust timer slack, ignoring: %m");

        if (arg_system && !cap_test_all(arg_capability_bounding_set)) {
                r = capability_bounding_set_drop_usermode(arg_capability_bounding_set);
                if (r < 0) {
                        *ret_error_message = "Failed to drop capability bounding set of usermode helpers";
                        return log_emergency_errno(r, "Failed to drop capability bounding set of usermode helpers: %m");
                }

                r = capability_bounding_set_drop(arg_capability_bounding_set, true);
                if (r < 0) {
                        *ret_error_message = "Failed to drop capability bounding set";
                        return log_emergency_errno(r, "Failed to drop capability bounding set: %m");
                }
        }

        if (arg_system && arg_no_new_privs) {
                if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0) {
                        *ret_error_message = "Failed to disable new privileges";
                        return log_emergency_errno(errno, "Failed to disable new privileges: %m");
                }
        }

        if (arg_syscall_archs) {
                r = enforce_syscall_archs(arg_syscall_archs);
                if (r < 0) {
                        *ret_error_message = "Failed to set syscall architectures";
                        return r;
                }
        }

        if (!arg_system)
                /* Become reaper of our children */
                if (prctl(PR_SET_CHILD_SUBREAPER, 1) < 0)
                        log_warning_errno(errno, "Failed to make us a subreaper: %m");

        /* Bump up RLIMIT_NOFILE for systemd itself */
        (void) bump_rlimit_nofile(saved_rlimit_nofile);
        (void) bump_rlimit_memlock(saved_rlimit_memlock);

        return 0;
}