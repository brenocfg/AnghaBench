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
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  unique_name; struct TYPE_10__* bus; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CLOSING ; 
 scalar_t__ BUS_HELLO ; 
 int /*<<< orphan*/  BUS_RUNNING ; 
 int EBADMSG ; 
 TYPE_1__* IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int sd_bus_message_get_errno (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**) ; 
 int /*<<< orphan*/  service_name_is_valid (char const*) ; 
 int synthesize_connected_signal (TYPE_1__*) ; 

__attribute__((used)) static int hello_callback(sd_bus_message *reply, void *userdata, sd_bus_error *error) {
        const char *s;
        sd_bus *bus;
        int r;

        assert(reply);
        bus = reply->bus;
        assert(bus);
        assert(IN_SET(bus->state, BUS_HELLO, BUS_CLOSING));

        r = sd_bus_message_get_errno(reply);
        if (r > 0) {
                r = -r;
                goto fail;
        }

        r = sd_bus_message_read(reply, "s", &s);
        if (r < 0)
                goto fail;

        if (!service_name_is_valid(s) || s[0] != ':') {
                r = -EBADMSG;
                goto fail;
        }

        r = free_and_strdup(&bus->unique_name, s);
        if (r < 0)
                goto fail;

        if (bus->state == BUS_HELLO) {
                bus_set_state(bus, BUS_RUNNING);

                r = synthesize_connected_signal(bus);
                if (r < 0)
                        goto fail;
        }

        return 1;

fail:
        /* When Hello() failed, let's propagate this in two ways: first we return the error immediately here,
         * which is the propagated up towards the event loop. Let's also invalidate the connection, so that
         * if the user then calls back into us again we won't wait any longer. */

        bus_set_state(bus, BUS_CLOSING);
        return r;
}