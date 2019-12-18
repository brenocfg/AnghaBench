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
struct TYPE_2__ {int /*<<< orphan*/  disable_controllers; } ;
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int cg_mask_from_string (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 

int config_parse_disable_controllers(
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

        int r;
        CGroupContext *c = data;
        CGroupMask disabled_mask;

        /* 1. If empty, make all controllers eligible for use again.
         * 2. If non-empty, merge all listed controllers, space separated. */

        if (isempty(rvalue)) {
                c->disable_controllers = 0;
                return 0;
        }

        r = cg_mask_from_string(rvalue, &disabled_mask);
        if (r < 0 || disabled_mask <= 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Invalid cgroup string: %s, ignoring", rvalue);
                return 0;
        }

        c->disable_controllers |= disabled_mask;

        return 0;
}