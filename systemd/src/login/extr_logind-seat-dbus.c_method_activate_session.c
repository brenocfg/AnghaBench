#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  id; TYPE_1__* manager; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_13__ {TYPE_2__* seat; } ;
struct TYPE_11__ {int /*<<< orphan*/  sessions; } ;
typedef  TYPE_3__ Session ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NO_SUCH_SESSION ; 
 int /*<<< orphan*/  BUS_ERROR_SESSION_NOT_ON_SEAT ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_3__* hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int sd_bus_message_read (TYPE_2__*,char*,char const**) ; 
 int sd_bus_reply_method_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int session_activate (TYPE_3__*) ; 

__attribute__((used)) static int method_activate_session(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Seat *s = userdata;
        const char *name;
        Session *session;
        int r;

        assert(message);
        assert(s);

        r = sd_bus_message_read(message, "s", &name);
        if (r < 0)
                return r;

        session = hashmap_get(s->manager->sessions, name);
        if (!session)
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_SESSION, "No session '%s' known", name);

        if (session->seat != s)
                return sd_bus_error_setf(error, BUS_ERROR_SESSION_NOT_ON_SEAT, "Session %s not on seat %s", name, s->id);

        r = session_activate(session);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}