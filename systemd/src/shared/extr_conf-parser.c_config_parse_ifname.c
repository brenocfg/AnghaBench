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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int free_and_strdup (char**,char const*) ; 
 int /*<<< orphan*/  ifname_valid (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 char* mfree (char*) ; 

int config_parse_ifname(
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

        char **s = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                *s = mfree(*s);
                return 0;
        }

        if (!ifname_valid(rvalue)) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Interface name is not valid or too long, ignoring assignment: %s", rvalue);
                return 0;
        }

        r = free_and_strdup(s, rvalue);
        if (r < 0)
                return log_oom();

        return 0;
}