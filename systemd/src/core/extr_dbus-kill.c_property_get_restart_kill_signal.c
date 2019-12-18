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
typedef  int /*<<< orphan*/  KillContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int restart_kill_signal (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append_basic (int /*<<< orphan*/ *,char,int*) ; 

__attribute__((used)) static int property_get_restart_kill_signal(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {
        KillContext *c = userdata;
        int s;

        assert(c);

        s = restart_kill_signal(c);
        return sd_bus_message_append_basic(reply, 'i', &s);
}