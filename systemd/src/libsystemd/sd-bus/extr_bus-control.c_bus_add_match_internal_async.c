#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_slot ;
typedef  int /*<<< orphan*/  sd_bus_message_handler_t ;
struct TYPE_6__ {int /*<<< orphan*/  bus_client; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int EINVAL ; 
 char* append_eavesdrop (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_call_method_async (TYPE_1__*,int /*<<< orphan*/ **,char*,char*,char*,char*,int /*<<< orphan*/ ,void*,char*,char const*) ; 

int bus_add_match_internal_async(
                sd_bus *bus,
                sd_bus_slot **ret_slot,
                const char *match,
                sd_bus_message_handler_t callback,
                void *userdata) {

        const char *e;

        assert(bus);

        if (!bus->bus_client)
                return -EINVAL;

        e = append_eavesdrop(bus, match);

        return sd_bus_call_method_async(
                        bus,
                        ret_slot,
                        "org.freedesktop.DBus",
                        "/org/freedesktop/DBus",
                        "org.freedesktop.DBus",
                        "AddMatch",
                        callback,
                        userdata,
                        "s",
                        e);
}