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
typedef  int /*<<< orphan*/  Session ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NOT_IN_CONTROL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_sender (int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_drop_controller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_is_controller (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int method_release_control(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Session *s = userdata;

        assert(message);
        assert(s);

        if (!session_is_controller(s, sd_bus_message_get_sender(message)))
                return sd_bus_error_setf(error, BUS_ERROR_NOT_IN_CONTROL, "You are not in control of this session");

        session_drop_controller(s);

        return sd_bus_reply_method_return(message, NULL);
}