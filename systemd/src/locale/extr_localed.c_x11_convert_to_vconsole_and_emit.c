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
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  sd_bus_emit_properties_changed (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int vconsole_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vconsole_reload (int /*<<< orphan*/ ) ; 
 int vconsole_write_data (int /*<<< orphan*/ *) ; 
 int x11_convert_to_vconsole (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x11_convert_to_vconsole_and_emit(Context *c, sd_bus_message *m) {
        int r;

        assert(m);

        r = vconsole_read_data(c, m);
        if (r < 0)
                return r;

        r = x11_convert_to_vconsole(c);
        if (r <= 0)
                return r;

        /* modified */
        r = vconsole_write_data(c);
        if (r < 0)
                log_error_errno(r, "Failed to save virtual console keymap: %m");

        sd_bus_emit_properties_changed(sd_bus_message_get_bus(m),
                                       "/org/freedesktop/locale1",
                                       "org.freedesktop.locale1",
                                       "VConsoleKeymap", "VConsoleKeymapToggle", NULL);

        return vconsole_reload(sd_bus_message_get_bus(m));
}