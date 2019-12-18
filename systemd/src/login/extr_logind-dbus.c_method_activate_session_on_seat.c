#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_4__ {int /*<<< orphan*/ * seat; } ;
typedef  TYPE_1__ Session ;
typedef  int /*<<< orphan*/  Seat ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_SESSION_NOT_ON_SEAT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int manager_get_seat_from_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int manager_get_session_from_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int session_activate (TYPE_1__*) ; 

__attribute__((used)) static int method_activate_session_on_seat(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const char *session_name, *seat_name;
        Manager *m = userdata;
        Session *session;
        Seat *seat;
        int r;

        assert(message);
        assert(m);

        /* Same as ActivateSession() but refuses to work if the seat doesn't match */

        r = sd_bus_message_read(message, "ss", &session_name, &seat_name);
        if (r < 0)
                return r;

        r = manager_get_session_from_creds(m, message, session_name, error, &session);
        if (r < 0)
                return r;

        r = manager_get_seat_from_creds(m, message, seat_name, error, &seat);
        if (r < 0)
                return r;

        if (session->seat != seat)
                return sd_bus_error_setf(error, BUS_ERROR_SESSION_NOT_ON_SEAT,
                                         "Session %s not on seat %s", session_name, seat_name);

        r = session_activate(session);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}