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
typedef  int /*<<< orphan*/  sd_bus_track ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_track_remove_name_fully (int /*<<< orphan*/ *,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**,char const**) ; 

__attribute__((used)) static int on_name_owner_changed(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        sd_bus_track *track = userdata;
        const char *name, *old, *new;
        int r;

        assert(message);
        assert(track);

        r = sd_bus_message_read(message, "sss", &name, &old, &new);
        if (r < 0)
                return 0;

        bus_track_remove_name_fully(track, name);
        return 0;
}