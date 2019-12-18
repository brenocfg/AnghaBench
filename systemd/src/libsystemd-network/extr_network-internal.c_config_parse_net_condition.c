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
typedef  int ConditionType ;
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/ * condition_free_list_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * condition_new (int,char const*,int,int) ; 
 int /*<<< orphan*/  conditions ; 
 scalar_t__ isempty (char const*) ; 
 int log_oom () ; 

int config_parse_net_condition(const char *unit,
                               const char *filename,
                               unsigned line,
                               const char *section,
                               unsigned section_line,
                               const char *lvalue,
                               int ltype,
                               const char *rvalue,
                               void *data,
                               void *userdata) {

        ConditionType cond = ltype;
        Condition **list = data, *c;
        bool negate;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                *list = condition_free_list_type(*list, cond);
                return 0;
        }

        negate = rvalue[0] == '!';
        if (negate)
                rvalue++;

        c = condition_new(cond, rvalue, false, negate);
        if (!c)
                return log_oom();

        /* Drop previous assignment. */
        *list = condition_free_list_type(*list, cond);

        LIST_PREPEND(conditions, *list, c);
        return 0;
}