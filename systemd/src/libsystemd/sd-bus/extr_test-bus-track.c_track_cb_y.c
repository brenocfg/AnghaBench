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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_track_get_bus (int /*<<< orphan*/ *) ; 
 int sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int track_cb_called_y ; 

__attribute__((used)) static int track_cb_y(sd_bus_track *t, void *userdata) {
        int r;

        log_error("TRACK CB Y");

        assert_se(!track_cb_called_y);
        track_cb_called_y = true;

        /* We got disconnected, let's close everything */

        r = sd_event_exit(sd_bus_get_event(sd_bus_track_get_bus(t)), EXIT_SUCCESS);
        assert_se(r >= 0);

        return 0;
}