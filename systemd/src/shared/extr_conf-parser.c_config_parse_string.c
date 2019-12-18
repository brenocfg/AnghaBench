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
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  empty_to_null (char const*) ; 
 scalar_t__ free_and_strdup (char**,int /*<<< orphan*/ ) ; 
 int log_oom () ; 

int config_parse_string(
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

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (free_and_strdup(s, empty_to_null(rvalue)) < 0)
                return log_oom();

        return 0;
}