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
typedef  unsigned int sd_bus_message ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int /*<<< orphan*/  assert (unsigned int*) ; 
 int sd_bus_message_enter_container (unsigned int*,char,char*) ; 
 int sd_bus_message_exit_container (unsigned int*) ; 
 int sd_bus_message_read (unsigned int*,char*,int*) ; 
 int sd_bus_message_rewind (unsigned int*,int) ; 
 int sd_bus_message_skip (unsigned int*,char*) ; 

__attribute__((used)) static int count_addresses(sd_bus_message *m, int af, unsigned *ret) {
        unsigned c = 0;
        int r;

        assert(m);
        assert(ret);

        while ((r = sd_bus_message_enter_container(m, 'r', "iay")) > 0) {
                int family;

                r = sd_bus_message_read(m, "i", &family);
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

        r = sd_bus_message_rewind(m, false);
        if (r < 0)
                return r;

        *ret = c;
        return 0;
}