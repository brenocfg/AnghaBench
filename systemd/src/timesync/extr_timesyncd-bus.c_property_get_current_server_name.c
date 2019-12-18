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
typedef  TYPE_1__* sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__* sd_bus ;
struct TYPE_8__ {int /*<<< orphan*/ * string; } ;
typedef  TYPE_1__ ServerName ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__**) ; 
 int sd_bus_message_append (TYPE_1__**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int property_get_current_server_name(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ServerName **s = userdata;

        assert(s);
        assert(bus);
        assert(reply);

        return sd_bus_message_append(reply, "s", *s ? (*s)->string : NULL);
}