#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iovec_wrapper {int dummy; } ;
struct TYPE_5__ {scalar_t__ is_pid1; scalar_t__ is_journald; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  LOG_TARGET_JOURNAL_OR_KMSG ; 
 int /*<<< orphan*/  SD_MESSAGE_COREDUMP_STR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STRINGIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_coredumps () ; 
 int gather_pid_metadata (struct iovec_wrapper*,TYPE_1__*) ; 
 int gather_pid_metadata_from_argv (struct iovec_wrapper*,TYPE_1__*,int,char**) ; 
 struct iovec_wrapper* iovw_free_free (struct iovec_wrapper*) ; 
 struct iovec_wrapper* iovw_new () ; 
 int /*<<< orphan*/  iovw_put_string_field (struct iovec_wrapper*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_notice (char*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_set_target (int /*<<< orphan*/ ) ; 
 int send_iovec (struct iovec_wrapper*,int /*<<< orphan*/ ) ; 
 int submit_coredump (TYPE_1__*,struct iovec_wrapper*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_kernel(int argc, char* argv[]) {
        Context context = {};
        struct iovec_wrapper *iovw;
        int r;

        log_debug("Processing coredump received from the kernel...");

        iovw = iovw_new();
        if (!iovw)
                return log_oom();

        (void) iovw_put_string_field(iovw, "MESSAGE_ID=", SD_MESSAGE_COREDUMP_STR);
        (void) iovw_put_string_field(iovw, "PRIORITY=", STRINGIFY(LOG_CRIT));

        /* Collect all process metadata passed by the kernel through argv[] */
        r = gather_pid_metadata_from_argv(iovw, &context, argc - 1, argv + 1);
        if (r < 0)
                goto finish;

        /* Collect the rest of the process metadata retrieved from the runtime */
        r = gather_pid_metadata(iovw, &context);
        if (r < 0)
                goto finish;

        if (!context.is_journald) {
                /* OK, now we know it's not the journal, hence we can make use of it now. */
                log_set_target(LOG_TARGET_JOURNAL_OR_KMSG);
                log_open();
        }

        /* If this is PID 1 disable coredump collection, we'll unlikely be able to process
         * it later on.
         *
         * FIXME: maybe we should disable coredumps generation from the beginning and
         * re-enable it only when we know it's either safe (ie we're not running OOM) or
         * it's not pid1 ? */
        if (context.is_pid1) {
                log_notice("Due to PID 1 having crashed coredump collection will now be turned off.");
                disable_coredumps();
        }

        if (context.is_journald || context.is_pid1)
                r = submit_coredump(&context, iovw, STDIN_FILENO);
        else
                r = send_iovec(iovw, STDIN_FILENO);

 finish:
        iovw = iovw_free_free(iovw);
        return r;
}