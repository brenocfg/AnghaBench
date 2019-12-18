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
struct TYPE_2__ {int required_for_online; scalar_t__ required_operstate_for_online; } ;
typedef  TYPE_1__ Network ;
typedef  scalar_t__ LinkOperationalState ;

/* Variables and functions */
 scalar_t__ LINK_OPERSTATE_DEGRADED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ link_operstate_from_string (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 
 int parse_boolean (char const*) ; 

int config_parse_required_for_online(
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

        Network *network = data;
        LinkOperationalState s;
        bool required = true;
        int r;

        if (isempty(rvalue)) {
                network->required_for_online = true;
                network->required_operstate_for_online = LINK_OPERSTATE_DEGRADED;
                return 0;
        }

        s = link_operstate_from_string(rvalue);
        if (s < 0) {
                r = parse_boolean(rvalue);
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r,
                                   "Failed to parse %s= setting, ignoring assignment: %s",
                                   lvalue, rvalue);
                        return 0;
                }

                required = r;
                s = LINK_OPERSTATE_DEGRADED;
        }

        network->required_for_online = required;
        network->required_operstate_for_online = s;

        return 0;
}