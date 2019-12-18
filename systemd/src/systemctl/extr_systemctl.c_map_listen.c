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

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_TYPE_ARRAY ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int strv_extend (char***,char const*) ; 

__attribute__((used)) static int map_listen(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        const char *type, *path;
        char ***p = userdata;
        int r;

        r = sd_bus_message_enter_container(m, SD_BUS_TYPE_ARRAY, "(ss)");
        if (r < 0)
                return r;

        while ((r = sd_bus_message_read(m, "(ss)", &type, &path)) > 0) {

                r = strv_extend(p, type);
                if (r < 0)
                        return r;

                r = strv_extend(p, path);
                if (r < 0)
                        return r;
        }
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return 0;
}