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
struct security_info {int system_call_filter_whitelist; int /*<<< orphan*/  system_call_filter; } ;
typedef  char const sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  char const sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int sd_bus_message_enter_container (char const*,char,char*) ; 
 int sd_bus_message_exit_container (char const*) ; 
 int sd_bus_message_read (char const*,char*,...) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put_strdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  string_hash_ops ; 

__attribute__((used)) static int property_read_system_call_filter(
                sd_bus *bus,
                const char *member,
                sd_bus_message *m,
                sd_bus_error *error,
                void *userdata) {

        struct security_info *info = userdata;
        int whitelist, r;

        assert(bus);
        assert(member);
        assert(m);

        r = sd_bus_message_enter_container(m, 'r', "bas");
        if (r < 0)
                return r;

        r = sd_bus_message_read(m, "b", &whitelist);
        if (r < 0)
                return r;

        info->system_call_filter_whitelist = whitelist;

        r = sd_bus_message_enter_container(m, 'a', "s");
        if (r < 0)
                return r;

        for (;;) {
                const char *name;

                r = sd_bus_message_read(m, "s", &name);
                if (r < 0)
                        return r;
                if (r == 0)
                        break;

                r = set_ensure_allocated(&info->system_call_filter, &string_hash_ops);
                if (r < 0)
                        return r;

                r = set_put_strdup(info->system_call_filter, name);
                if (r < 0)
                        return r;
        }

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return sd_bus_message_exit_container(m);
}