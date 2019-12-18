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
typedef  int uint8_t ;

/* Variables and functions */
 int IPPROTO_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int UINT8_MAX ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_ip_protocol (char const*) ; 
 int safe_atou8 (char const*,int*) ; 

int config_parse_ip_protocol(
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

        uint8_t *protocol = data;
        int r;

        assert(filename);
        assert(section);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        assert_cc(IPPROTO_MAX-1 <= UINT8_MAX);

        r = parse_ip_protocol(rvalue);
        if (r < 0) {
                r = safe_atou8(rvalue, protocol);
                if (r < 0)
                        log_syntax(unit, LOG_ERR, filename, line, r,
                                   "Failed to parse IP protocol '%s' for Foo over UDP tunnel, "
                                   "ignoring assignment: %m", rvalue);
                return 0;
        }

        *protocol = r;
        return 0;
}