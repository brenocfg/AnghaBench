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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  User ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_user_method_kill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int manager_get_user_from_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_kill_user(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        uint32_t uid;
        User *user;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "u", &uid);
        if (r < 0)
                return r;

        r = manager_get_user_from_creds(m, message, uid, error, &user);
        if (r < 0)
                return r;

        return bus_user_method_kill(message, user, error);
}