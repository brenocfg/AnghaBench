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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NOT_REFERENCED ; 
 int EUNATCH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_unit_track_remove_sender (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bus_unit_method_unref(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Unit *u = userdata;
        int r;

        assert(message);
        assert(u);

        r = bus_unit_track_remove_sender(u, message);
        if (r == -EUNATCH)
                return sd_bus_error_setf(error, BUS_ERROR_NOT_REFERENCED, "Unit has not been referenced yet.");
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}