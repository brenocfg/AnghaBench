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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ LINK_BRIDGE_PORT_PRIORITY_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,scalar_t__,...) ; 
 int safe_atou16 (char const*,scalar_t__*) ; 

int config_parse_bridge_port_priority(
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

        uint16_t i;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atou16(rvalue, &i);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Failed to parse bridge port priority, ignoring: %s", rvalue);
                return 0;
        }

        if (i > LINK_BRIDGE_PORT_PRIORITY_MAX) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Bridge port priority is larger than maximum %u, ignoring: %s", LINK_BRIDGE_PORT_PRIORITY_MAX, rvalue);
                return 0;
        }

        *((uint16_t *)data) = i;

        return 0;
}