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
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_NULL ; 
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/ * condition_free_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  conditions ; 
 scalar_t__ isempty (char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_boolean (char const*) ; 

int config_parse_unit_condition_null(
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

        Condition **list = data, *c;
        bool trigger, negate;
        int b;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        log_syntax(unit, LOG_WARNING, filename, line, 0, "%s= is deprecated, please do not use.", lvalue);

        if (isempty(rvalue)) {
                /* Empty assignment resets the list */
                *list = condition_free_list(*list);
                return 0;
        }

        trigger = rvalue[0] == '|';
        if (trigger)
                rvalue++;

        negate = rvalue[0] == '!';
        if (negate)
                rvalue++;

        b = parse_boolean(rvalue);
        if (b < 0) {
                log_syntax(unit, LOG_ERR, filename, line, b, "Failed to parse boolean value in condition, ignoring: %s", rvalue);
                return 0;
        }

        if (!b)
                negate = !negate;

        c = condition_new(CONDITION_NULL, NULL, trigger, negate);
        if (!c)
                return log_oom();

        LIST_PREPEND(conditions, *list, c);
        return 0;
}