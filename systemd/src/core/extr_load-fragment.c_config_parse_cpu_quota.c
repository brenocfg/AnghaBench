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
typedef  unsigned int usec_t ;
struct TYPE_2__ {unsigned int cpu_quota_per_sec_usec; } ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 unsigned int USEC_INFINITY ; 
 unsigned int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_permille_unbounded (char const*) ; 

int config_parse_cpu_quota(
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

        CGroupContext *c = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);

        if (isempty(rvalue)) {
                c->cpu_quota_per_sec_usec = USEC_INFINITY;
                return 0;
        }

        r = parse_permille_unbounded(rvalue);
        if (r <= 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Invalid CPU quota '%s', ignoring.", rvalue);
                return 0;
        }

        c->cpu_quota_per_sec_usec = ((usec_t) r * USEC_PER_SEC) / 1000U;
        return 0;
}