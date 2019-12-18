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
struct TYPE_2__ {int cpu_sched_priority; int cpu_sched_set; int /*<<< orphan*/  cpu_sched_policy; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int safe_atoi (char const*,int*) ; 
 int sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int sched_get_priority_min (int /*<<< orphan*/ ) ; 

int config_parse_exec_cpu_sched_prio(const char *unit,
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
        int i, min, max, r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atoi(rvalue, &i);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse CPU scheduling priority, ignoring: %s", rvalue);
                return 0;
        }

        /* On Linux RR/FIFO range from 1 to 99 and OTHER/BATCH may only be 0 */
        min = sched_get_priority_min(c->cpu_sched_policy);
        max = sched_get_priority_max(c->cpu_sched_policy);

        if (i < min || i > max) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "CPU scheduling priority is out of range, ignoring: %s", rvalue);
                return 0;
        }

        c->cpu_sched_priority = i;
        c->cpu_sched_set = true;

        return 0;
}