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
 scalar_t__ ADDRESS_FAMILY_NO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ address_family_from_string (char const*) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_address_family_with_kernel(
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

        AddressFamily *fwd = data, s;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        /* This function is mostly obsolete now. It simply redirects
         * "kernel" to "no". In older networkd versions we used to
         * distinguish IPForward=off from IPForward=kernel, where the
         * former would explicitly turn off forwarding while the
         * latter would simply not touch the setting. But that logic
         * is gone, hence silently accept the old setting, but turn it
         * to "no". */

        s = address_family_from_string(rvalue);
        if (s < 0) {
                if (streq(rvalue, "kernel"))
                        s = ADDRESS_FAMILY_NO;
                else {
                        log_syntax(unit, LOG_ERR, filename, line, 0, "Failed to parse IPForward= option, ignoring: %s", rvalue);
                        return 0;
                }
        }

        *fwd = s;

        return 0;
}