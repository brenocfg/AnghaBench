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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int default_memory_low_set; int default_memory_min_set; int memory_min_set; int memory_low_set; scalar_t__ memory_limit; scalar_t__ memory_swap_max; scalar_t__ memory_max; scalar_t__ memory_high; scalar_t__ memory_low; scalar_t__ memory_min; void* default_memory_min; void* default_memory_low; } ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 scalar_t__ CGROUP_LIMIT_MAX ; 
 void* CGROUP_LIMIT_MIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  STR_IN_SET (char const*,char*,char*,char*,char*,char*) ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_permille (char const*) ; 
 int parse_size (char const*,int,scalar_t__*) ; 
 scalar_t__ physical_memory_scale (int,unsigned int) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_memory_limit(
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
        uint64_t bytes = CGROUP_LIMIT_MAX;
        int r;

        if (!isempty(rvalue) && !streq(rvalue, "infinity")) {

                r = parse_permille(rvalue);
                if (r < 0) {
                        r = parse_size(rvalue, 1024, &bytes);
                        if (r < 0) {
                                log_syntax(unit, LOG_ERR, filename, line, r, "Invalid memory limit '%s', ignoring: %m", rvalue);
                                return 0;
                        }
                } else
                        bytes = physical_memory_scale(r, 1000U);

                if (bytes >= UINT64_MAX ||
                    (bytes <= 0 && !STR_IN_SET(lvalue, "MemorySwapMax", "MemoryLow", "MemoryMin", "DefaultMemoryLow", "DefaultMemoryMin"))) {
                        log_syntax(unit, LOG_ERR, filename, line, 0, "Memory limit '%s' out of range, ignoring.", rvalue);
                        return 0;
                }
        }

        if (streq(lvalue, "DefaultMemoryLow")) {
                c->default_memory_low_set = true;
                if (isempty(rvalue))
                        c->default_memory_low = CGROUP_LIMIT_MIN;
                else
                        c->default_memory_low = bytes;
        } else if (streq(lvalue, "DefaultMemoryMin")) {
                c->default_memory_min_set = true;
                if (isempty(rvalue))
                        c->default_memory_min = CGROUP_LIMIT_MIN;
                else
                        c->default_memory_min = bytes;
        } else if (streq(lvalue, "MemoryMin")) {
                c->memory_min = bytes;
                c->memory_min_set = true;
        } else if (streq(lvalue, "MemoryLow")) {
                c->memory_low = bytes;
                c->memory_low_set = true;
        } else if (streq(lvalue, "MemoryHigh"))
                c->memory_high = bytes;
        else if (streq(lvalue, "MemoryMax"))
                c->memory_max = bytes;
        else if (streq(lvalue, "MemorySwapMax"))
                c->memory_swap_max = bytes;
        else if (streq(lvalue, "MemoryLimit"))
                c->memory_limit = bytes;
        else
                return -EINVAL;

        return 0;
}