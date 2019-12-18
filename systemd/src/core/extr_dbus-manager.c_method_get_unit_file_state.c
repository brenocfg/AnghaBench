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
struct TYPE_8__ {int /*<<< orphan*/  unit_file_scope; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitFileState ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**) ; 
 int sd_bus_reply_method_return (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int unit_file_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_file_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int method_get_unit_file_state(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        const char *name;
        UnitFileState state;
        int r;

        assert(message);
        assert(m);

        /* Anyone can call this method */

        r = mac_selinux_access_check(message, "status", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "s", &name);
        if (r < 0)
                return r;

        r = unit_file_get_state(m->unit_file_scope, NULL, name, &state);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, "s", unit_file_state_to_string(state));
}