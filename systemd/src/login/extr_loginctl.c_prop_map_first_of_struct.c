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
 int /*<<< orphan*/  SD_BUS_TYPE_STRUCT ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_peek_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int sd_bus_message_read_basic (int /*<<< orphan*/ *,char const,void*) ; 
 int sd_bus_message_skip (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int prop_map_first_of_struct(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        const char *contents;
        int r;

        r = sd_bus_message_peek_type(m, NULL, &contents);
        if (r < 0)
                return r;

        r = sd_bus_message_enter_container(m, SD_BUS_TYPE_STRUCT, contents);
        if (r < 0)
                return r;

        r = sd_bus_message_read_basic(m, contents[0], userdata);
        if (r < 0)
                return r;

        r = sd_bus_message_skip(m, contents+1);
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return 0;
}