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
typedef  int /*<<< orphan*/  AddressFamily ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FAMILY_IPV4 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char const* address_family_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*,char const*) ; 
 int parse_boolean (char const*) ; 

int config_parse_ipv4ll(
                const char* unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        AddressFamily *link_local = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        /* Note that this is mostly like
         * config_parse_address_family(), except that it
         * applies only to IPv4 */

        r = parse_boolean(rvalue);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Failed to parse %s=%s, ignoring assignment. "
                           "Note that the setting %s= is deprecated, please use LinkLocalAddressing= instead.",
                           lvalue, rvalue, lvalue);
                return 0;
        }

        SET_FLAG(*link_local, ADDRESS_FAMILY_IPV4, r);

        log_syntax(unit, LOG_WARNING, filename, line, 0,
                   "%s=%s is deprecated, please use LinkLocalAddressing=%s instead.",
                   lvalue, rvalue, address_family_to_string(*link_local));

        return 0;
}