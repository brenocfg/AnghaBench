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
 int /*<<< orphan*/  HIGH_RLIMIT_NOFILE ; 
 int /*<<< orphan*/  LC_ALL ; 
 char* ansi_highlight_red () ; 
 char* ansi_normal () ; 
 int check_units_active () ; 
 int coredumpctl_main (int,char**) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_show_color (int) ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,char*) ; 
 int /*<<< orphan*/  rlimit_nofile_bump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigbus_install () ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r, units_active;

        setlocale(LC_ALL, "");
        log_show_color(true);
        log_parse_environment();
        log_open();

        /* The journal merging logic potentially needs a lot of fds. */
        (void) rlimit_nofile_bump(HIGH_RLIMIT_NOFILE);

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        sigbus_install();

        units_active = check_units_active(); /* error is treated the same as 0 */

        r = coredumpctl_main(argc, argv);

        if (units_active > 0)
                printf("%s-- Notice: %d systemd-coredump@.service %s, output may be incomplete.%s\n",
                       ansi_highlight_red(),
                       units_active, units_active == 1 ? "unit is running" : "units are running",
                       ansi_normal());
        return r;
}