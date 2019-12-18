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
struct TYPE_2__ {int /*<<< orphan*/  pivot_root_old; int /*<<< orphan*/  pivot_root_new; } ;
typedef  TYPE_1__ Settings ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int pivot_root_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int config_parse_pivot_root(
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

        Settings *settings = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);

        r = pivot_root_parse(&settings->pivot_root_new, &settings->pivot_root_old, rvalue);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Invalid pivot root mount specification %s: %m", rvalue);
                return 0;
        }

        return 0;
}