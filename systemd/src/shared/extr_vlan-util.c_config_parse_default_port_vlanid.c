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
 int /*<<< orphan*/  assert (void*) ; 
 int config_parse_vlanid (char const*,char const*,unsigned int,char const*,unsigned int,char const*,int,char const*,void*,void*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_default_port_vlanid(
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
        uint16_t *id = data;

        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (streq(rvalue, "none")) {
                *id = 0;
                return 0;
        }

        return config_parse_vlanid(unit, filename, line, section, section_line,
                                   lvalue, ltype, rvalue, data, userdata);
}