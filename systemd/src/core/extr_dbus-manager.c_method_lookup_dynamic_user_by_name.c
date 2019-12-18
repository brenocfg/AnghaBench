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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NO_SUCH_DYNAMIC_USER ; 
 int ESRCH ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dynamic_user_lookup_name (int /*<<< orphan*/ *,char const*,scalar_t__*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int sd_bus_message_read_basic (int /*<<< orphan*/ *,char,char const**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_user_group_name (char const*) ; 

__attribute__((used)) static int method_lookup_dynamic_user_by_name(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        const char *name;
        uid_t uid;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read_basic(message, 's', &name);
        if (r < 0)
                return r;

        if (!MANAGER_IS_SYSTEM(m))
                return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Dynamic users are only supported in the system instance.");
        if (!valid_user_group_name(name))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "User name invalid: %s", name);

        r = dynamic_user_lookup_name(m, name, &uid);
        if (r == -ESRCH)
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_DYNAMIC_USER, "Dynamic user %s does not exist.", name);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, "u", (uint32_t) uid);
}