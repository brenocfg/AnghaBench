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
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_message_is_method_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client2_callback(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        assert_se(sd_bus_message_is_method_error(m, NULL) == 0);
        assert_se(sd_event_exit(sd_bus_get_event(sd_bus_message_get_bus(m)), 0) >= 0);
        return 0;
}