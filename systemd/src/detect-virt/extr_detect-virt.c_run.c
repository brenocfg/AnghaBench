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
#define  ANY_VIRTUALIZATION 132 
#define  ONLY_CHROOT 131 
#define  ONLY_CONTAINER 130 
#define  ONLY_PRIVATE_USERS 129 
#define  ONLY_VM 128 
 int VIRTUALIZATION_NONE ; 
 int arg_mode ; 
 int /*<<< orphan*/  arg_quiet ; 
 int detect_container () ; 
 int detect_virtualization () ; 
 int detect_vm () ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_show_color (int) ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int running_in_chroot () ; 
 int running_in_userns () ; 
 int /*<<< orphan*/  virtualization_to_string (int) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        /* This is mostly intended to be used for scripts which want
         * to detect whether we are being run in a virtualized
         * environment or not */

        log_show_color(true);
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        switch (arg_mode) {
        case ONLY_VM:
                r = detect_vm();
                if (r < 0)
                        return log_error_errno(r, "Failed to check for VM: %m");
                break;

        case ONLY_CONTAINER:
                r = detect_container();
                if (r < 0)
                        return log_error_errno(r, "Failed to check for container: %m");
                break;

        case ONLY_CHROOT:
                r = running_in_chroot();
                if (r < 0)
                        return log_error_errno(r, "Failed to check for chroot() environment: %m");
                return !r;

        case ONLY_PRIVATE_USERS:
                r = running_in_userns();
                if (r < 0)
                        return log_error_errno(r, "Failed to check for user namespace: %m");
                return !r;

        case ANY_VIRTUALIZATION:
        default:
                r = detect_virtualization();
                if (r < 0)
                        return log_error_errno(r, "Failed to check for virtualization: %m");
                break;
        }

        if (!arg_quiet)
                puts(virtualization_to_string(r));

        return r == VIRTUALIZATION_NONE;
}