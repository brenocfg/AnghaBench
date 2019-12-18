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
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
typedef  TYPE_1__ NUMAPolicy ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_cpu_set_extend (char const*,int /*<<< orphan*/ *,int,char const*,char const*,unsigned int,char const*) ; 

int config_parse_numa_mask(const char *unit,
                           const char *filename,
                           unsigned line,
                           const char *section,
                           unsigned section_line,
                           const char *lvalue,
                           int ltype,
                           const char *rvalue,
                           void *data,
                           void *userdata) {
        int r;
        NUMAPolicy *p = data;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = parse_cpu_set_extend(rvalue, &p->nodes, true, unit, filename, line, lvalue);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse NUMA node mask, ignoring: %s", rvalue);
                return 0;
        }

        return r;
}