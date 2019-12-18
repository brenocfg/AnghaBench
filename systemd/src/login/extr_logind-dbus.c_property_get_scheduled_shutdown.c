#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  scheduled_shutdown_timeout; int /*<<< orphan*/  scheduled_shutdown_type; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_message_close_container (TYPE_1__*) ; 
 int sd_bus_message_open_container (TYPE_1__*,char,char*) ; 

__attribute__((used)) static int property_get_scheduled_shutdown(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        int r;

        assert(bus);
        assert(reply);
        assert(m);

        r = sd_bus_message_open_container(reply, 'r', "st");
        if (r < 0)
                return r;

        r = sd_bus_message_append(reply, "st", m->scheduled_shutdown_type, m->scheduled_shutdown_timeout);
        if (r < 0)
                return r;

        return sd_bus_message_close_container(reply);
}