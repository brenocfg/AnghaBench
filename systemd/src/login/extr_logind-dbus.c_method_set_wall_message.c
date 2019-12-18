#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int enable_wall_messages; int /*<<< orphan*/  wall_message; int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_to_null (char*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int log_oom () ; 
 int sd_bus_message_read (TYPE_1__*,char*,char**,unsigned int*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_set_wall_message(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        int r;
        Manager *m = userdata;
        char *wall_message;
        unsigned enable_wall_messages;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "sb", &wall_message, &enable_wall_messages);
        if (r < 0)
                return r;

        r = bus_verify_polkit_async(message,
                                    CAP_SYS_ADMIN,
                                    "org.freedesktop.login1.set-wall-message",
                                    NULL,
                                    false,
                                    UID_INVALID,
                                    &m->polkit_registry,
                                    error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        r = free_and_strdup(&m->wall_message, empty_to_null(wall_message));
        if (r < 0)
                return log_oom();

        m->enable_wall_messages = enable_wall_messages;

        return sd_bus_reply_method_return(message, NULL);
}