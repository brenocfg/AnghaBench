#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int action_what; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int INHIBIT_SHUTDOWN ; 
 int INHIBIT_SLEEP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int property_get_preparing(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        bool b;

        assert(bus);
        assert(reply);
        assert(m);

        if (streq(property, "PreparingForShutdown"))
                b = m->action_what & INHIBIT_SHUTDOWN;
        else
                b = m->action_what & INHIBIT_SLEEP;

        return sd_bus_message_append(reply, "b", b);
}