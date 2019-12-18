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
 int LOG_FACMASK ; 
 int /*<<< orphan*/  assert (void*) ; 
 int log_level_from_string (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 

int config_parse_log_level(
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

        int *o = data, x;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        x = log_level_from_string(rvalue);
        if (x < 0) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Failed to parse log level, ignoring: %s", rvalue);
                return 0;
        }

        if (*o < 0) /* if it wasn't initialized so far, assume zero facility */
                *o = x;
        else
                *o = (*o & LOG_FACMASK) | x;

        return 0;
}