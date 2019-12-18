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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int manager_get_session_from_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int session_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_release_session(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        Session *session;
        const char *name;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "s", &name);
        if (r < 0)
                return r;

        r = manager_get_session_from_creds(m, message, name, error, &session);
        if (r < 0)
                return r;

        r = session_release(session);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}