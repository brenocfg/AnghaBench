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
struct TYPE_2__ {int cpu_sched_set; int cpu_sched_policy; scalar_t__ cpu_sched_priority; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 scalar_t__ CLAMP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SCHED_OTHER ; 
 int /*<<< orphan*/  assert (void*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  sched_get_priority_max (int) ; 
 int /*<<< orphan*/  sched_get_priority_min (int) ; 
 int sched_policy_from_string (char const*) ; 

int config_parse_exec_cpu_sched_policy(const char *unit,
                                       const char *filename,
                                       unsigned line,
                                       const char *section,
                                       unsigned section_line,
                                       const char *lvalue,
                                       int ltype,
                                       const char *rvalue,
                                       void *data,
                                       void *userdata) {

        ExecContext *c = data;
        int x;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                c->cpu_sched_set = false;
                c->cpu_sched_policy = SCHED_OTHER;
                c->cpu_sched_priority = 0;
                return 0;
        }

        x = sched_policy_from_string(rvalue);
        if (x < 0) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Failed to parse CPU scheduling policy, ignoring: %s", rvalue);
                return 0;
        }

        c->cpu_sched_policy = x;
        /* Moving to or from real-time policy? We need to adjust the priority */
        c->cpu_sched_priority = CLAMP(c->cpu_sched_priority, sched_get_priority_min(x), sched_get_priority_max(x));
        c->cpu_sched_set = true;

        return 0;
}