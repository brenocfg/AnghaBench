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
 scalar_t__ ACTION_QUERY ; 
 scalar_t__ arg_action ; 
 scalar_t__ arg_console ; 
 scalar_t__ arg_device ; 
 int ask_on_consoles (char**) ; 
 int /*<<< orphan*/  log_setup_service () ; 
 int parse_argv (int,char**) ; 
 int process_and_watch_password_files (int) ; 
 int /*<<< orphan*/  release_terminal () ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  umask (int) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        log_setup_service();

        umask(0022);

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (arg_console && !arg_device)
                /*
                 * Spawn a separate process for each console device.
                 */
                return ask_on_consoles(argv);

        if (arg_device) {
                /*
                 * Later on, a controlling terminal will be acquired,
                 * therefore the current process has to become a session
                 * leader and should not have a controlling terminal already.
                 */
                (void) setsid();
                (void) release_terminal();
        }

        return process_and_watch_password_files(arg_action != ACTION_QUERY);
}