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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  TEST_REQ_RUNNING_SYSTEMD (int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  parse_pid (char*,int*) ; 
 int /*<<< orphan*/  save_argc_argv (int,char**) ; 
 int /*<<< orphan*/  test_get_process_cmdline_harder () ; 
 int /*<<< orphan*/  test_get_process_comm (int) ; 
 int /*<<< orphan*/  test_get_process_comm_escape () ; 
 int /*<<< orphan*/  test_getpid_cached () ; 
 int /*<<< orphan*/  test_getpid_measure () ; 
 int /*<<< orphan*/  test_ioprio_class_from_to_string () ; 
 int /*<<< orphan*/  test_personality () ; 
 int /*<<< orphan*/  test_pid_is_alive () ; 
 int /*<<< orphan*/  test_pid_is_unwaited () ; 
 int /*<<< orphan*/  test_pid_to_ptr () ; 
 int /*<<< orphan*/  test_rename_process () ; 
 int /*<<< orphan*/  test_safe_fork () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        save_argc_argv(argc, argv);

        if (argc > 1) {
                pid_t pid = 0;

                (void) parse_pid(argv[1], &pid);
                test_get_process_comm(pid);
        } else {
                TEST_REQ_RUNNING_SYSTEMD(test_get_process_comm(1));
                test_get_process_comm(getpid());
        }

        test_get_process_comm_escape();
        test_pid_is_unwaited();
        test_pid_is_alive();
        test_personality();
        test_get_process_cmdline_harder();
        test_rename_process();
        test_getpid_cached();
        test_getpid_measure();
        test_safe_fork();
        test_pid_to_ptr();
        test_ioprio_class_from_to_string();

        return 0;
}