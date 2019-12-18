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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  sd_bus_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_disconnected(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        assert(m);

        log_error("Warning! D-Bus connection terminated.");
        sd_bus_close(sd_bus_message_get_bus(m));

        return 0;
}