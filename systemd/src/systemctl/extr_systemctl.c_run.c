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
#define  ACTION_CANCEL_SHUTDOWN 149 
#define  ACTION_DEFAULT 148 
#define  ACTION_EMERGENCY 147 
#define  ACTION_EXIT 146 
#define  ACTION_HALT 145 
#define  ACTION_HIBERNATE 144 
#define  ACTION_HYBRID_SLEEP 143 
#define  ACTION_KEXEC 142 
#define  ACTION_POWEROFF 141 
#define  ACTION_REBOOT 140 
#define  ACTION_REEXEC 139 
#define  ACTION_RELOAD 138 
#define  ACTION_RESCUE 137 
#define  ACTION_RUNLEVEL 136 
#define  ACTION_RUNLEVEL2 135 
#define  ACTION_RUNLEVEL3 134 
#define  ACTION_RUNLEVEL4 133 
#define  ACTION_RUNLEVEL5 132 
#define  ACTION_SUSPEND 131 
#define  ACTION_SUSPEND_THEN_HIBERNATE 130 
#define  ACTION_SYSTEMCTL 129 
 int /*<<< orphan*/  HIGH_RLIMIT_NOFILE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
#define  _ACTION_INVALID 128 
 int arg_action ; 
 int /*<<< orphan*/  arg_quiet ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int halt_main () ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int logind_cancel_shutdown () ; 
 int /*<<< orphan*/  original_stdout_is_tty ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  release_busses () ; 
 int reload_with_fallback () ; 
 int /*<<< orphan*/  rlimit_nofile_bump (int /*<<< orphan*/ ) ; 
 int runlevel_main () ; 
 scalar_t__ running_in_chroot () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigbus_install () ; 
 int start_with_fallback () ; 
 int systemctl_main (int,char**) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        setlocale(LC_ALL, "");
        log_parse_environment();
        log_open();

        /* The journal merging logic potentially needs a lot of fds. */
        (void) rlimit_nofile_bump(HIGH_RLIMIT_NOFILE);

        sigbus_install();

        /* Explicitly not on_tty() to avoid setting cached value.
         * This becomes relevant for piping output which might be
         * ellipsized. */
        original_stdout_is_tty = isatty(STDOUT_FILENO);

        r = parse_argv(argc, argv);
        if (r <= 0)
                goto finish;

        if (arg_action != ACTION_SYSTEMCTL && running_in_chroot() > 0) {
                if (!arg_quiet)
                        log_info("Running in chroot, ignoring request.");
                r = 0;
                goto finish;
        }

        /* systemctl_main() will print an error message for the bus
         * connection, but only if it needs to */

        switch (arg_action) {

        case ACTION_SYSTEMCTL:
                r = systemctl_main(argc, argv);
                break;

        /* Legacy command aliases set arg_action. They provide some fallbacks,
         * e.g. to tell sysvinit to reboot after you have installed systemd
         * binaries. */

        case ACTION_HALT:
        case ACTION_POWEROFF:
        case ACTION_REBOOT:
        case ACTION_KEXEC:
                r = halt_main();
                break;

        case ACTION_RUNLEVEL2:
        case ACTION_RUNLEVEL3:
        case ACTION_RUNLEVEL4:
        case ACTION_RUNLEVEL5:
        case ACTION_RESCUE:
                r = start_with_fallback();
                break;

        case ACTION_RELOAD:
        case ACTION_REEXEC:
                r = reload_with_fallback();
                break;

        case ACTION_CANCEL_SHUTDOWN:
                r = logind_cancel_shutdown();
                break;

        case ACTION_RUNLEVEL:
                r = runlevel_main();
                break;

        case ACTION_EXIT:
        case ACTION_SUSPEND:
        case ACTION_HIBERNATE:
        case ACTION_HYBRID_SLEEP:
        case ACTION_SUSPEND_THEN_HIBERNATE:
        case ACTION_EMERGENCY:
        case ACTION_DEFAULT:
                /* systemctl verbs with no equivalent in the legacy commands.
                 * These cannot appear in arg_action.  Fall through. */

        case _ACTION_INVALID:
        default:
                assert_not_reached("Unknown action");
        }

finish:
        release_busses();

        /* Note that we return r here, not 0, so that we can implement the LSB-like return codes */
        return r;
}