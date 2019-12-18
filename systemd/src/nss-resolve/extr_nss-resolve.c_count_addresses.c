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
typedef  char const* sd_bus_message ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int /*<<< orphan*/  assert (char const**) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int sd_bus_message_enter_container (char const**,char,char*) ; 
 int sd_bus_message_exit_container (char const**) ; 
 int sd_bus_message_read (char const**,char*,...) ; 
 int sd_bus_message_rewind (char const**,int) ; 
 int sd_bus_message_skip (char const**,char*) ; 

__attribute__((used)) static int count_addresses(sd_bus_message *m, int af, const char **canonical) {
        int c = 0, r;

        assert(m);
        assert(canonical);

        r = sd_bus_message_enter_container(m, 'a', "(iiay)");
        if (r < 0)
                return r;

        while ((r = sd_bus_message_enter_container(m, 'r', "iiay")) > 0) {
                int family, ifindex;

                assert_cc(sizeof(int32_t) == sizeof(int));

                r = sd_bus_message_read(m, "ii", &ifindex, &family);
                if (r < 0)
                        return r;

                r = sd_bus_message_skip(m, "ay");
                if (r < 0)
                        return r;

                r = sd_bus_message_exit_container(m);
                if (r < 0)
                        return r;

                if (af != AF_UNSPEC && family != af)
                        continue;

                c++;
        }
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        r = sd_bus_message_read(m, "s", canonical);
        if (r < 0)
                return r;

        r = sd_bus_message_rewind(m, true);
        if (r < 0)
                return r;

        return c;
}