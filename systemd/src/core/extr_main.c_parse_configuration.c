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
 scalar_t__ arg_system ; 
 int /*<<< orphan*/  assert (struct rlimit const*) ; 
 int /*<<< orphan*/  fallback_rlimit_memlock (struct rlimit const*) ; 
 int /*<<< orphan*/  fallback_rlimit_nofile (struct rlimit const*) ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int parse_config_file () ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_arguments () ; 

__attribute__((used)) static int parse_configuration(const struct rlimit *saved_rlimit_nofile,
                               const struct rlimit *saved_rlimit_memlock) {
        int r;

        assert(saved_rlimit_nofile);
        assert(saved_rlimit_memlock);

        /* Assign configuration defaults */
        reset_arguments();

        r = parse_config_file();
        if (r < 0)
                log_warning_errno(r, "Failed to parse config file, ignoring: %m");

        if (arg_system) {
                r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, 0);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");
        }

        /* Initialize some default rlimits for services if they haven't been configured */
        fallback_rlimit_nofile(saved_rlimit_nofile);
        fallback_rlimit_memlock(saved_rlimit_memlock);

        /* Note that this also parses bits from the kernel command line, including "debug". */
        log_parse_environment();

        return 0;
}