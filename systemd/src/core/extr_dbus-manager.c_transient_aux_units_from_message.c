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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int transient_unit_from_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int transient_aux_units_from_message(
                Manager *m,
                sd_bus_message *message,
                sd_bus_error *error) {

        int r;

        assert(m);
        assert(message);

        r = sd_bus_message_enter_container(message, 'a', "(sa(sv))");
        if (r < 0)
                return r;

        while ((r = sd_bus_message_enter_container(message, 'r', "sa(sv)")) > 0) {
                const char *name = NULL;
                Unit *u;

                r = sd_bus_message_read(message, "s", &name);
                if (r < 0)
                        return r;

                r = transient_unit_from_message(m, message, name, &u, error);
                if (r < 0)
                        return r;

                r = sd_bus_message_exit_container(message);
                if (r < 0)
                        return r;
        }
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(message);
        if (r < 0)
                return r;

        return 0;
}