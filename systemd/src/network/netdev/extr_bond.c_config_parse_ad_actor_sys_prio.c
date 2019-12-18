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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ ad_actor_sys_prio; } ;
typedef  TYPE_1__ Bond ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int safe_atou16 (char const*,scalar_t__*) ; 

int config_parse_ad_actor_sys_prio(
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
        Bond *b = userdata;
        uint16_t v;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atou16(rvalue, &v);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Failed to parse actor system priority '%s', ignoring: %m", rvalue);
                return 0;
        }

        if (v == 0) {
                log_syntax(unit, LOG_ERR, filename, line, 0,
                           "Failed to parse actor system priority '%s'. Range is [1,65535], ignoring.",
                           rvalue);
                return 0;
        }

        b->ad_actor_sys_prio = v;

        return 0;
}