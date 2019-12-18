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
typedef  char** sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char***) ; 
 int sd_bus_message_enter_container (char***,char,char*) ; 
 int sd_bus_message_exit_container (char***) ; 
 int sd_bus_message_read_basic (char***,char,char const**) ; 
 int strv_extend (char***,char const*) ; 

int bus_message_read_strv_extend(sd_bus_message *m, char ***l) {
        const char *s;
        int r;

        assert(m);
        assert(l);

        r = sd_bus_message_enter_container(m, 'a', "s");
        if (r <= 0)
                return r;

        while ((r = sd_bus_message_read_basic(m, 's', &s)) > 0) {
                r = strv_extend(l, s);
                if (r < 0)
                        return r;
        }
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return 1;
}