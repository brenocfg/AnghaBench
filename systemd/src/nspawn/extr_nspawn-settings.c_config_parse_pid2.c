#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ start_mode; } ;
typedef  TYPE_1__ Settings ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ START_BOOT ; 
 scalar_t__ START_PID1 ; 
 scalar_t__ START_PID2 ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,...) ; 
 int parse_boolean (char const*) ; 

int config_parse_pid2(
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

        Settings *settings = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);

        r = parse_boolean(rvalue);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse ProcessTwo= parameter %s, ignoring: %m", rvalue);
                return 0;
        }

        if (r > 0) {
                if (settings->start_mode == START_BOOT)
                        goto conflict;

                settings->start_mode = START_PID2;
        } else {
                if (settings->start_mode == START_PID2)
                        goto conflict;

                if (settings->start_mode < 0)
                        settings->start_mode = START_PID1;
        }

        return 0;

conflict:
        log_syntax(unit, LOG_ERR, filename, line, r, "Conflicting Boot= or ProcessTwo= setting found. Ignoring.");
        return 0;
}