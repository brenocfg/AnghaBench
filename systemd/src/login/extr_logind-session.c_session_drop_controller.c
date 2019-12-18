#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  track; int /*<<< orphan*/  controller; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_release_controller (TYPE_1__*,int) ; 
 int /*<<< orphan*/  session_restore_vt (TYPE_1__*) ; 
 int /*<<< orphan*/  session_save (TYPE_1__*) ; 

void session_drop_controller(Session *s) {
        assert(s);

        if (!s->controller)
                return;

        s->track = sd_bus_track_unref(s->track);
        session_release_controller(s, false);
        session_save(s);
        session_restore_vt(s);
}