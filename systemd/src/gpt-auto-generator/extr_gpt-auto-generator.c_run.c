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
 int add_mounts () ; 
 int add_root_mount () ; 
 char const* arg_dest ; 
 int /*<<< orphan*/  arg_enabled ; 
 scalar_t__ arg_root_enabled ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 scalar_t__ detect_container () ; 
 int /*<<< orphan*/  in_initrd () ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(const char *dest, const char *dest_early, const char *dest_late) {
        int r, k;

        assert_se(arg_dest = dest_late);

        if (detect_container() > 0) {
                log_debug("In a container, exiting.");
                return 0;
        }

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, 0);
        if (r < 0)
                log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");

        if (!arg_enabled) {
                log_debug("Disabled, exiting.");
                return 0;
        }

        if (arg_root_enabled)
                r = add_root_mount();

        if (!in_initrd()) {
                k = add_mounts();
                if (r >= 0)
                        r = k;
        }

        return r;
}