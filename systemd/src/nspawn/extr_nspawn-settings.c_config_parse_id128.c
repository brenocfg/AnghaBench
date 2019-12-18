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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int sd_id128_from_string (char const*,int /*<<< orphan*/ *) ; 

int config_parse_id128(
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

        sd_id128_t t, *result = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);

        r = sd_id128_from_string(rvalue, &t);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse 128bit ID/UUID, ignoring: %s", rvalue);
                return 0;
        }

        *result = t;
        return 0;
}