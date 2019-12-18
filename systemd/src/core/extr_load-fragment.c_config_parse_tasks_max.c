#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_3__ {scalar_t__ default_tasks_max; } ;

/* Variables and functions */
 scalar_t__ CGROUP_LIMIT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_permille (char const*) ; 
 int safe_atou64 (char const*,scalar_t__*) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ system_tasks_max_scale (int,unsigned int) ; 

int config_parse_tasks_max(
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

        uint64_t *tasks_max = data, v;
        const Unit *u = userdata;
        int r;

        if (isempty(rvalue)) {
                *tasks_max = u ? u->manager->default_tasks_max : UINT64_MAX;
                return 0;
        }

        if (streq(rvalue, "infinity")) {
                *tasks_max = CGROUP_LIMIT_MAX;
                return 0;
        }

        r = parse_permille(rvalue);
        if (r < 0) {
                r = safe_atou64(rvalue, &v);
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r, "Invalid maximum tasks value '%s', ignoring: %m", rvalue);
                        return 0;
                }
        } else
                v = system_tasks_max_scale(r, 1000U);

        if (v <= 0 || v >= UINT64_MAX) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Maximum tasks value '%s' out of range, ignoring.", rvalue);
                return 0;
        }

        *tasks_max = v;
        return 0;
}