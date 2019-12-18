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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;
typedef  scalar_t__ ConditionType ;
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 scalar_t__ CONDITION_NULL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int UNIT_ESCAPE_SPECIFIERS ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 scalar_t__ assert_type_from_string (char const*) ; 
 int /*<<< orphan*/ * condition_free_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (scalar_t__,char const*,int,int) ; 
 scalar_t__ condition_takes_path (scalar_t__) ; 
 scalar_t__ condition_type_from_string (char const*) ; 
 int /*<<< orphan*/  conditions ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  path_is_absolute (char const*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,int*,int*,char const**) ; 
 int /*<<< orphan*/  unit_write_settingf (int /*<<< orphan*/ *,int,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/  yes_no (int) ; 

__attribute__((used)) static int bus_set_transient_conditions(
                Unit *u,
                const char *name,
                Condition **list,
                bool is_condition,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        const char *type_name, *param;
        int trigger, negate, r;
        bool empty = true;

        assert(list);

        r = sd_bus_message_enter_container(message, 'a', "(sbbs)");
        if (r < 0)
                return r;

        while ((r = sd_bus_message_read(message, "(sbbs)", &type_name, &trigger, &negate, &param)) > 0) {
                ConditionType t;

                t = is_condition ? condition_type_from_string(type_name) : assert_type_from_string(type_name);
                if (t < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid condition type: %s", type_name);

                if (t != CONDITION_NULL) {
                        if (isempty(param))
                                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Condition parameter in %s is empty", type_name);

                        if (condition_takes_path(t) && !path_is_absolute(param))
                                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Path in condition %s is not absolute: %s", type_name, param);
                } else
                        param = NULL;

                if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                        Condition *c;

                        c = condition_new(t, param, trigger, negate);
                        if (!c)
                                return -ENOMEM;

                        LIST_PREPEND(conditions, *list, c);

                        if (t != CONDITION_NULL)
                                unit_write_settingf(u, flags|UNIT_ESCAPE_SPECIFIERS, name,
                                                    "%s=%s%s%s", type_name,
                                                    trigger ? "|" : "", negate ? "!" : "", param);
                        else
                                unit_write_settingf(u, flags, name,
                                                    "%s=%s%s", type_name,
                                                    trigger ? "|" : "", yes_no(!negate));
                }

                empty = false;
        }
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(message);
        if (r < 0)
                return r;

        if (!UNIT_WRITE_FLAGS_NOOP(flags) && empty) {
                *list = condition_free_list(*list);
                unit_write_settingf(u, flags, name, "%sNull=", is_condition ? "Condition" : "Assert");
        }

        return 1;
}