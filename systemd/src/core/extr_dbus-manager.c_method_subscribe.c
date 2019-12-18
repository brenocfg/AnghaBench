#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ api_bus; int /*<<< orphan*/  subscribed; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_ALREADY_SUBSCRIBED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sd_bus_track_add_sender (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_bus_track_new (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_subscribe(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        int r;

        assert(message);
        assert(m);

        /* Anyone can call this method */

        r = mac_selinux_access_check(message, "status", error);
        if (r < 0)
                return r;

        if (sd_bus_message_get_bus(message) == m->api_bus) {

                /* Note that direct bus connection subscribe by
                 * default, we only track peers on the API bus here */

                if (!m->subscribed) {
                        r = sd_bus_track_new(sd_bus_message_get_bus(message), &m->subscribed, NULL, NULL);
                        if (r < 0)
                                return r;
                }

                r = sd_bus_track_add_sender(m->subscribed, message);
                if (r < 0)
                        return r;
                if (r == 0)
                        return sd_bus_error_setf(error, BUS_ERROR_ALREADY_SUBSCRIBED, "Client is already subscribed.");
        }

        return sd_bus_reply_method_return(message, NULL);
}