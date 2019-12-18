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
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_emit_properties_changed_strv (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_changed_signal(sd_bus *bus, void *userdata) {
        assert(bus);

        return sd_bus_emit_properties_changed_strv(bus,
                                                   "/org/freedesktop/systemd1",
                                                   "org.freedesktop.systemd1.Manager",
                                                   NULL);
}