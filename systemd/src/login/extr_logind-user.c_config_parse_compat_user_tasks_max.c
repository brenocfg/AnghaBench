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
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 

int config_parse_compat_user_tasks_max(
                const char *unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        log_syntax(unit, LOG_NOTICE, filename, line, 0,
                   "Support for option %s= has been removed.",
                   lvalue);
        log_info("Hint: try creating /etc/systemd/system/user-.slice.d/50-limits.conf with:\n"
                 "        [Slice]\n"
                 "        TasksMax=%s",
                 rvalue);
        return 0;
}