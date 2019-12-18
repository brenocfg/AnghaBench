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
typedef  int /*<<< orphan*/  Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_drop_controller (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_bus_track(sd_bus_track *track, void *userdata) {
        Session *s = userdata;

        assert(track);
        assert(s);

        session_drop_controller(s);

        return 0;
}