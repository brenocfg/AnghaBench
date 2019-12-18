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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_TARGET_KMSG ; 
 int /*<<< orphan*/  PR_SET_DUMPABLE ; 
 int /*<<< orphan*/  SD_LISTEN_FDS_START ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_compress ; 
 int /*<<< orphan*/  arg_storage ; 
 int /*<<< orphan*/  coredump_storage_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_set_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_config () ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_backtrace (int,char**) ; 
 int process_kernel (int,char**) ; 
 int process_socket (int /*<<< orphan*/ ) ; 
 int sd_listen_fds (int) ; 
 scalar_t__ streq_ptr (char*,char*) ; 
 int /*<<< orphan*/  yes_no (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        /* First, log to a safe place, since we don't know what crashed and it might
         * be journald which we'd rather not log to then. */

        log_set_target(LOG_TARGET_KMSG);
        log_open();

        /* Make sure we never enter a loop */
        (void) prctl(PR_SET_DUMPABLE, 0);

        /* Ignore all parse errors */
        (void) parse_config();

        log_debug("Selected storage '%s'.", coredump_storage_to_string(arg_storage));
        log_debug("Selected compression %s.", yes_no(arg_compress));

        r = sd_listen_fds(false);
        if (r < 0)
                return log_error_errno(r, "Failed to determine the number of file descriptors: %m");

        /* If we got an fd passed, we are running in coredumpd mode. Otherwise we
         * are invoked from the kernel as coredump handler. */
        if (r == 0) {
                if (streq_ptr(argv[1], "--backtrace"))
                        return process_backtrace(argc, argv);
                else
                        return process_kernel(argc, argv);
        } else if (r == 1)
                return process_socket(SD_LISTEN_FDS_START);

        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                               "Received unexpected number of file descriptors.");
}