#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ load_state; scalar_t__ transient; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int UnitWriteFlags ;
typedef  TYPE_1__ Unit ;
struct TYPE_19__ {int (* bus_set_property ) (TYPE_1__*,char const*,TYPE_1__*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* bus_commit_properties ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_PROPERTY_READ_ONLY ; 
 int UNIT_PERSISTENT ; 
 int UNIT_RUNTIME ; 
 scalar_t__ UNIT_STUB ; 
 TYPE_17__* UNIT_VTABLE (TYPE_1__*) ; 
 scalar_t__ UNIT_WRITE_FLAGS_NOOP (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_unit_set_live_property (TYPE_1__*,char const*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int bus_unit_set_transient_property (TYPE_1__*,char const*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int sd_bus_message_enter_container (TYPE_1__*,char,char*) ; 
 int sd_bus_message_exit_container (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**) ; 
 int sd_bus_message_rewind (TYPE_1__*,int) ; 
 int stub1 (TYPE_1__*,char const*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

int bus_unit_set_properties(
                Unit *u,
                sd_bus_message *message,
                UnitWriteFlags flags,
                bool commit,
                sd_bus_error *error) {

        bool for_real = false;
        unsigned n = 0;
        int r;

        assert(u);
        assert(message);

        /* We iterate through the array twice. First run we just check
         * if all passed data is valid, second run actually applies
         * it. This is to implement transaction-like behaviour without
         * actually providing full transactions. */

        r = sd_bus_message_enter_container(message, 'a', "(sv)");
        if (r < 0)
                return r;

        for (;;) {
                const char *name;
                UnitWriteFlags f;

                r = sd_bus_message_enter_container(message, 'r', "sv");
                if (r < 0)
                        return r;
                if (r == 0) {
                        if (for_real || UNIT_WRITE_FLAGS_NOOP(flags))
                                break;

                        /* Reached EOF. Let's try again, and this time for realz... */
                        r = sd_bus_message_rewind(message, false);
                        if (r < 0)
                                return r;

                        for_real = true;
                        continue;
                }

                r = sd_bus_message_read(message, "s", &name);
                if (r < 0)
                        return r;

                if (!UNIT_VTABLE(u)->bus_set_property)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_PROPERTY_READ_ONLY, "Objects of this type do not support setting properties.");

                r = sd_bus_message_enter_container(message, 'v', NULL);
                if (r < 0)
                        return r;

                /* If not for real, then mask out the two target flags */
                f = for_real ? flags : (flags & ~(UNIT_RUNTIME|UNIT_PERSISTENT));

                r = UNIT_VTABLE(u)->bus_set_property(u, name, message, f, error);
                if (r == 0 && u->transient && u->load_state == UNIT_STUB)
                        r = bus_unit_set_transient_property(u, name, message, f, error);
                if (r == 0)
                        r = bus_unit_set_live_property(u, name, message, f, error);
                if (r < 0)
                        return r;

                if (r == 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_PROPERTY_READ_ONLY, "Cannot set property %s, or unknown property.", name);

                r = sd_bus_message_exit_container(message);
                if (r < 0)
                        return r;

                r = sd_bus_message_exit_container(message);
                if (r < 0)
                        return r;

                n += for_real;
        }

        r = sd_bus_message_exit_container(message);
        if (r < 0)
                return r;

        if (commit && n > 0 && UNIT_VTABLE(u)->bus_commit_properties)
                UNIT_VTABLE(u)->bus_commit_properties(u);

        return n;
}