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
struct security_info {int device_allow_non_empty; } ;
typedef  char const sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  char const sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int sd_bus_message_enter_container (char const*,char,char*) ; 
 int sd_bus_message_exit_container (char const*) ; 
 int sd_bus_message_read (char const*,char*,char const**,char const**) ; 

__attribute__((used)) static int property_read_device_allow(
                sd_bus *bus,
                const char *member,
                sd_bus_message *m,
                sd_bus_error *error,
                void *userdata) {

        struct security_info *info = userdata;
        size_t n = 0;
        int r;

        assert(bus);
        assert(member);
        assert(m);

        r = sd_bus_message_enter_container(m, 'a', "(ss)");
        if (r < 0)
                return r;

        for (;;) {
                const char *name, *policy;

                r = sd_bus_message_read(m, "(ss)", &name, &policy);
                if (r < 0)
                        return r;
                if (r == 0)
                        break;

                n++;
        }

        info->device_allow_non_empty = n > 0;

        return sd_bus_message_exit_container(m);
}