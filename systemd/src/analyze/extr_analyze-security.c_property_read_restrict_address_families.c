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
struct security_info {int restrict_address_family_inet; int restrict_address_family_unix; int restrict_address_family_netlink; int restrict_address_family_packet; int restrict_address_family_other; } ;
typedef  char const sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  char const sd_bus ;

/* Variables and functions */
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int sd_bus_message_enter_container (char const*,char,char*) ; 
 int sd_bus_message_exit_container (char const*) ; 
 int sd_bus_message_read (char const*,char*,...) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int property_read_restrict_address_families(
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

        info->restrict_address_family_inet =
                info->restrict_address_family_unix =
                info->restrict_address_family_netlink =
                info->restrict_address_family_packet =
                info->restrict_address_family_other = whitelist;

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

                if (STR_IN_SET(name, "AF_INET", "AF_INET6"))
                        info->restrict_address_family_inet = !whitelist;
                else if (streq(name, "AF_UNIX"))
                        info->restrict_address_family_unix = !whitelist;
                else if (streq(name, "AF_NETLINK"))
                        info->restrict_address_family_netlink = !whitelist;
                else if (streq(name, "AF_PACKET"))
                        info->restrict_address_family_packet = !whitelist;
                else
                        info->restrict_address_family_other = !whitelist;
        }

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return sd_bus_message_exit_container(m);
}