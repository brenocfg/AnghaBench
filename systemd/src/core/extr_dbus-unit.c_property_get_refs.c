#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_2__ {int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char const*) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 
 int sd_bus_track_count_name (int /*<<< orphan*/ ,char const*) ; 
 char* sd_bus_track_first (int /*<<< orphan*/ ) ; 
 char* sd_bus_track_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int property_get_refs(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Unit *u = userdata;
        const char *i;
        int r;

        assert(bus);
        assert(reply);

        r = sd_bus_message_open_container(reply, 'a', "s");
        if (r < 0)
                return r;

        for (i = sd_bus_track_first(u->bus_track); i; i = sd_bus_track_next(u->bus_track)) {
                int c, k;

                c = sd_bus_track_count_name(u->bus_track, i);
                if (c < 0)
                        return c;

                /* Add the item multiple times if the ref count for each is above 1 */
                for (k = 0; k < c; k++) {
                        r = sd_bus_message_append(reply, "s", i);
                        if (r < 0)
                                return r;
                }
        }

        return sd_bus_message_close_container(reply);
}