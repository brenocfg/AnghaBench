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
typedef  int /*<<< orphan*/  UnitType ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int config_parse_strv (char const*,char const*,unsigned int,char const*,unsigned int,char const*,int,char const*,void*,void*) ; 
 int log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_name_to_type (char const*) ; 
 int /*<<< orphan*/  unit_type_may_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_parse_alias(
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

        UnitType type;

        assert(unit);
        assert(filename);
        assert(lvalue);
        assert(rvalue);

        type = unit_name_to_type(unit);
        if (!unit_type_may_alias(type))
                return log_syntax(unit, LOG_WARNING, filename, line, 0,
                                  "Alias= is not allowed for %s units, ignoring.",
                                  unit_type_to_string(type));

        return config_parse_strv(unit, filename, line, section, section_line,
                                 lvalue, ltype, rvalue, data, userdata);
}