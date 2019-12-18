#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_track ;
struct TYPE_3__ {int /*<<< orphan*/  controller_track; scalar_t__ controller; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ mfree (scalar_t__) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_controller_gone(sd_bus_track *track, void *userdata) {
        Scope *s = userdata;

        assert(track);

        if (s->controller) {
                log_unit_debug(UNIT(s), "Controller %s disappeared from bus.", s->controller);
                unit_add_to_dbus_queue(UNIT(s));
                s->controller = mfree(s->controller);
        }

        s->controller_track = sd_bus_track_unref(s->controller_track);

        return 0;
}