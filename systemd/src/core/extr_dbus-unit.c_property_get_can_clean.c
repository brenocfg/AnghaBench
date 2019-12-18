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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  Unit ;
typedef  unsigned int ExecDirectoryType ;
typedef  int /*<<< orphan*/  ExecCleanMask ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_SET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int _EXEC_DIRECTORY_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_resource_type_to_string (unsigned int) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 
 int unit_can_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int property_get_can_clean(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Unit *u = userdata;
        ExecCleanMask mask;
        int r;

        assert(bus);
        assert(reply);

        r = unit_can_clean(u, &mask);
        if (r < 0)
                return r;

        r = sd_bus_message_open_container(reply, 'a', "s");
        if (r < 0)
                return r;

        for (ExecDirectoryType t = 0; t < _EXEC_DIRECTORY_TYPE_MAX; t++) {
                if (!FLAGS_SET(mask, 1U << t))
                        continue;

                r = sd_bus_message_append(reply, "s", exec_resource_type_to_string(t));
                if (r < 0)
                        return r;
        }

        return sd_bus_message_close_container(reply);
}