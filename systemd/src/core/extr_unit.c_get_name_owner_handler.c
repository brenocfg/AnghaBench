#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  get_name_owner_slot; } ;
typedef  TYPE_1__ sd_bus_message ;
struct TYPE_17__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_2__ sd_bus_error ;
typedef  TYPE_1__ Unit ;
struct TYPE_15__ {int /*<<< orphan*/  (* bus_name_owner_change ) (TYPE_1__*,int /*<<< orphan*/ *,char const*) ;} ;

/* Variables and functions */
 TYPE_13__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 char* empty_to_null (char const*) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_bus_error_has_name (TYPE_2__ const*,char*) ; 
 scalar_t__ sd_bus_error_is_set (TYPE_2__*) ; 
 TYPE_2__* sd_bus_message_get_error (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int get_name_owner_handler(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const sd_bus_error *e;
        const char *new_owner;
        Unit *u = userdata;
        int r;

        assert(message);
        assert(u);

        u->get_name_owner_slot = sd_bus_slot_unref(u->get_name_owner_slot);

        if (sd_bus_error_is_set(error)) {
                log_error("Failed to get name owner from bus: %s", error->message);
                return 0;
        }

        e = sd_bus_message_get_error(message);
        if (sd_bus_error_has_name(e, "org.freedesktop.DBus.Error.NameHasNoOwner"))
                return 0;

        if (e) {
                log_error("Unexpected error response from GetNameOwner: %s", e->message);
                return 0;
        }

        r = sd_bus_message_read(message, "s", &new_owner);
        if (r < 0) {
                bus_log_parse_error(r);
                return 0;
        }

        new_owner = empty_to_null(new_owner);

        if (UNIT_VTABLE(u)->bus_name_owner_change)
                UNIT_VTABLE(u)->bus_name_owner_change(u, NULL, new_owner);

        return 0;
}