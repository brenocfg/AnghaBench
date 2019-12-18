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
struct TYPE_8__ {char* working_directory; scalar_t__ working_directory_missing_ok; scalar_t__ working_directory_home; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,char const*) ; 
 char* strjoina (char*,char const*) ; 

__attribute__((used)) static int property_get_working_directory(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ExecContext *c = userdata;
        const char *wd;

        assert(bus);
        assert(reply);
        assert(c);

        if (c->working_directory_home)
                wd = "~";
        else
                wd = c->working_directory;

        if (c->working_directory_missing_ok)
                wd = strjoina("!", wd);

        return sd_bus_message_append(reply, "s", wd);
}