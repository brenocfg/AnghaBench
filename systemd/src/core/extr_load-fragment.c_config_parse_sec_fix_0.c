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
typedef  char const usec_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 
 int parse_sec_fix_0 (char const*,char const*) ; 

int config_parse_sec_fix_0(
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

        usec_t *usec = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(usec);

        /* This is pretty much like config_parse_sec(), except that this treats a time of 0 as infinity, for
         * compatibility with older versions of systemd where 0 instead of infinity was used as indicator to turn off a
         * timeout. */

        r = parse_sec_fix_0(rvalue, usec);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse %s= parameter, ignoring: %s", lvalue, rvalue);
                return 0;
        }

        return 0;
}