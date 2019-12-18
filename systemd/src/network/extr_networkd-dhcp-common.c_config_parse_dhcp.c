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
typedef  scalar_t__ AddressFamily ;

/* Variables and functions */
 scalar_t__ ADDRESS_FAMILY_IPV4 ; 
 scalar_t__ ADDRESS_FAMILY_IPV6 ; 
 scalar_t__ ADDRESS_FAMILY_NO ; 
 scalar_t__ ADDRESS_FAMILY_YES ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ address_family_from_string (char const*) ; 
 int /*<<< orphan*/  address_family_to_string (scalar_t__) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_dhcp(
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

        AddressFamily *dhcp = data, s;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        /* Note that this is mostly like
         * config_parse_address_family(), except that it
         * understands some old names for the enum values */

        s = address_family_from_string(rvalue);
        if (s < 0) {

                /* Previously, we had a slightly different enum here,
                 * support its values for compatibility. */

                if (streq(rvalue, "none"))
                        s = ADDRESS_FAMILY_NO;
                else if (streq(rvalue, "v4"))
                        s = ADDRESS_FAMILY_IPV4;
                else if (streq(rvalue, "v6"))
                        s = ADDRESS_FAMILY_IPV6;
                else if (streq(rvalue, "both"))
                        s = ADDRESS_FAMILY_YES;
                else {
                        log_syntax(unit, LOG_ERR, filename, line, 0,
                                   "Failed to parse DHCP option, ignoring: %s", rvalue);
                        return 0;
                }

                log_syntax(unit, LOG_WARNING, filename, line, 0,
                           "DHCP=%s is deprecated, please use DHCP=%s instead.",
                           rvalue, address_family_to_string(s));
        }

        *dhcp = s;
        return 0;
}