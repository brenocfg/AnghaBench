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
 int PROC_CMDLINE_RD_STRICT ; 
 int PROC_CMDLINE_STRIP_RD_PREFIX ; 
 scalar_t__ arg_debug_shell ; 
 char const* arg_dest ; 
 int /*<<< orphan*/  arg_wants ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int generate_mask_symlinks () ; 
 int generate_wants_symlinks () ; 
 int /*<<< orphan*/  install_debug_shell_dropin (char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strv_extend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int run(const char *dest, const char *dest_early, const char *dest_late) {
        int r, q;

        assert_se(arg_dest = dest_early);

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, PROC_CMDLINE_RD_STRICT | PROC_CMDLINE_STRIP_RD_PREFIX);
        if (r < 0)
                log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");

        if (arg_debug_shell) {
                r = strv_extend(&arg_wants, "debug-shell.service");
                if (r < 0)
                        return log_oom();

                install_debug_shell_dropin(arg_dest);
        }

        r = generate_mask_symlinks();
        q = generate_wants_symlinks();

        return r < 0 ? r : q;
}