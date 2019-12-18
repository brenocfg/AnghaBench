#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* manager; } ;
struct TYPE_9__ {scalar_t__ controller_track; int /*<<< orphan*/  controller; } ;
struct TYPE_8__ {int /*<<< orphan*/  api_bus; } ;
typedef  TYPE_2__ Scope ;

/* Variables and functions */
 TYPE_6__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  on_controller_gone ; 
 int sd_bus_track_add_name (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_bus_track_new (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ sd_bus_track_unref (scalar_t__) ; 

int bus_scope_track_controller(Scope *s) {
        int r;

        assert(s);

        if (!s->controller || s->controller_track)
                return 0;

        r = sd_bus_track_new(UNIT(s)->manager->api_bus, &s->controller_track, on_controller_gone, s);
        if (r < 0)
                return r;

        r = sd_bus_track_add_name(s->controller_track, s->controller);
        if (r < 0) {
                s->controller_track = sd_bus_track_unref(s->controller_track);
                return r;
        }

        return 0;
}