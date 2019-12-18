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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_ip_port (char const*,scalar_t__*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_wireguard_listen_port(
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

        uint16_t *s = data;
        int r;

        assert(rvalue);
        assert(data);

        if (isempty(rvalue) || streq(rvalue, "auto")) {
                *s = 0;
                return 0;
        }

        r = parse_ip_port(rvalue, s);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Invalid port specification, ignoring assignment: %s", rvalue);
                return 0;
        }

        return 0;
}