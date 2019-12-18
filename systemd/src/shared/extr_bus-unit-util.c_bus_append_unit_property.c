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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  scalar_t__ ConditionType ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_UNQUOTE ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*,...) ; 
 scalar_t__ _CONDITION_TYPE_INVALID ; 
 scalar_t__ assert_type_from_string (char const*) ; 
 int bus_append_parse_boolean (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_parse_sec_rename (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_safe_atou (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_strv (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int bus_log_create_error (int) ; 
 scalar_t__ condition_type_from_string (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int log_error_errno (int,char*,char const*,char const*) ; 
 int safe_atou8 (char const*,scalar_t__*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char const*,char*,int,...) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ unit_dependency_from_string (char const*) ; 

__attribute__((used)) static int bus_append_unit_property(sd_bus_message *m, const char *field, const char *eq) {
        ConditionType t = _CONDITION_TYPE_INVALID;
        bool is_condition = false;
        int r;

        if (STR_IN_SET(field,
                       "Description", "SourcePath", "OnFailureJobMode",
                       "JobTimeoutAction", "JobTimeoutRebootArgument",
                       "StartLimitAction", "FailureAction", "SuccessAction",
                       "RebootArgument", "CollectMode"))
                return bus_append_string(m, field, eq);

        if (STR_IN_SET(field,
                       "StopWhenUnneeded", "RefuseManualStart", "RefuseManualStop",
                       "AllowIsolate", "IgnoreOnIsolate", "DefaultDependencies"))
                return bus_append_parse_boolean(m, field, eq);

        if (STR_IN_SET(field, "JobTimeoutSec", "JobRunningTimeoutSec", "StartLimitIntervalSec"))
                return bus_append_parse_sec_rename(m, field, eq);

        if (streq(field, "StartLimitBurst"))
                return bus_append_safe_atou(m, field, eq);

        if (STR_IN_SET(field, "SuccessActionExitStatus", "FailureActionExitStatus")) {
                if (isempty(eq))
                        r = sd_bus_message_append(m, "(sv)", field, "i", -1);
                else {
                        uint8_t u;

                        r = safe_atou8(eq, &u);
                        if (r < 0)
                                return log_error_errno(r, "Failed to parse %s=%s", field, eq);

                        r = sd_bus_message_append(m, "(sv)", field, "i", (int) u);
                }
                if (r < 0)
                        return bus_log_create_error(r);

                return 1;
        }

        if (unit_dependency_from_string(field) >= 0 ||
            STR_IN_SET(field, "Documentation", "RequiresMountsFor"))
                return bus_append_strv(m, field, eq, EXTRACT_UNQUOTE);

        t = condition_type_from_string(field);
        if (t >= 0)
                is_condition = true;
        else
                t = assert_type_from_string(field);
        if (t >= 0) {
                if (isempty(eq))
                        r = sd_bus_message_append(m, "(sv)", is_condition ? "Conditions" : "Asserts", "a(sbbs)", 0);
                else {
                        const char *p = eq;
                        int trigger, negate;

                        trigger = *p == '|';
                        if (trigger)
                                p++;

                        negate = *p == '!';
                        if (negate)
                                p++;

                        r = sd_bus_message_append(m, "(sv)", is_condition ? "Conditions" : "Asserts", "a(sbbs)", 1,
                                                  field, trigger, negate, p);
                }
                if (r < 0)
                        return bus_log_create_error(r);

                return 1;
        }

        return 0;
}