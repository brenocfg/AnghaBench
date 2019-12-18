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
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 char* arg_dest ; 
 scalar_t__ arg_noresume ; 
 int /*<<< orphan*/  in_initrd () ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_notice (char*) ; 
 int /*<<< orphan*/  log_setup_generator () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int process_resume () ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r = 0;

        log_setup_generator();

        if (argc > 1 && argc != 4)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "This program takes three or no arguments.");

        if (argc > 1)
                arg_dest = argv[1];

        /* Don't even consider resuming outside of initramfs. */
        if (!in_initrd()) {
                log_debug("Not running in an initrd, quitting.");
                return 0;
        }

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, 0);
        if (r < 0)
                log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");

        if (arg_noresume) {
                log_notice("Found \"noresume\" on the kernel command line, quitting.");
                return 0;
        }

        return process_resume();
}