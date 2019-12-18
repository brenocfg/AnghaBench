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
typedef  int /*<<< orphan*/  ExecCommand ;

/* Variables and functions */
 int append_exec_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 

int bus_property_get_exec_command(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *ret_error) {

        ExecCommand *c = (ExecCommand*) userdata;
        int r;

        assert(bus);
        assert(reply);

        r = sd_bus_message_open_container(reply, 'a', "(sasbttttuii)");
        if (r < 0)
                return r;

        r = append_exec_command(reply, c);
        if (r < 0)
                return r;

        return sd_bus_message_close_container(reply);
}