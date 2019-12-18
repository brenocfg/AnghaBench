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
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  sd_bus_get_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_track_get_bus (int /*<<< orphan*/ *) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int track_cb_called_x ; 

__attribute__((used)) static int track_cb_x(sd_bus_track *t, void *userdata) {

        log_error("TRACK CB X");

        assert_se(!track_cb_called_x);
        track_cb_called_x = true;

        /* This means b's name disappeared. Let's now disconnect, to make sure the track handling on disconnect works
         * as it should. */

        assert_se(shutdown(sd_bus_get_fd(sd_bus_track_get_bus(t)), SHUT_RDWR) >= 0);
        return 1;
}