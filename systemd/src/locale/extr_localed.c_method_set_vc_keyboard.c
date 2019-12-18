#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vc_keymap_toggle; int /*<<< orphan*/  vc_keymap; int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SD_BUS_ERROR_FAILED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* empty_to_null (char const*) ; 
 int /*<<< orphan*/  filename_is_valid (char const*) ; 
 scalar_t__ free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_emit_properties_changed (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,char const**,int*,int*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strempty (int /*<<< orphan*/ ) ; 
 scalar_t__ streq_ptr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_safe (char const*) ; 
 int vconsole_convert_to_x11_and_emit (TYPE_1__*,TYPE_1__*) ; 
 int vconsole_read_data (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vconsole_reload (int /*<<< orphan*/ ) ; 
 int vconsole_write_data (TYPE_1__*) ; 

__attribute__((used)) static int method_set_vc_keyboard(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        Context *c = userdata;
        const char *keymap, *keymap_toggle;
        int convert, interactive, r;

        assert(m);
        assert(c);

        r = sd_bus_message_read(m, "ssbb", &keymap, &keymap_toggle, &convert, &interactive);
        if (r < 0)
                return r;

        keymap = empty_to_null(keymap);
        keymap_toggle = empty_to_null(keymap_toggle);

        r = vconsole_read_data(c, m);
        if (r < 0) {
                log_error_errno(r, "Failed to read virtual console keymap data: %m");
                return sd_bus_error_setf(error, SD_BUS_ERROR_FAILED, "Failed to read virtual console keymap data");
        }

        if (streq_ptr(keymap, c->vc_keymap) &&
            streq_ptr(keymap_toggle, c->vc_keymap_toggle))
                return sd_bus_reply_method_return(m, NULL);

        if ((keymap && (!filename_is_valid(keymap) || !string_is_safe(keymap))) ||
            (keymap_toggle && (!filename_is_valid(keymap_toggle) || !string_is_safe(keymap_toggle))))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Received invalid keymap data");

        r = bus_verify_polkit_async(
                        m,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.locale1.set-keyboard",
                        NULL,
                        interactive,
                        UID_INVALID,
                        &c->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        if (free_and_strdup(&c->vc_keymap, keymap) < 0 ||
            free_and_strdup(&c->vc_keymap_toggle, keymap_toggle) < 0)
                return -ENOMEM;

        r = vconsole_write_data(c);
        if (r < 0) {
                log_error_errno(r, "Failed to set virtual console keymap: %m");
                return sd_bus_error_set_errnof(error, r, "Failed to set virtual console keymap: %m");
        }

        log_info("Changed virtual console keymap to '%s' toggle '%s'",
                 strempty(c->vc_keymap), strempty(c->vc_keymap_toggle));

        (void) vconsole_reload(sd_bus_message_get_bus(m));

        (void) sd_bus_emit_properties_changed(
                        sd_bus_message_get_bus(m),
                        "/org/freedesktop/locale1",
                        "org.freedesktop.locale1",
                        "VConsoleKeymap", "VConsoleKeymapToggle", NULL);

        if (convert) {
                r = vconsole_convert_to_x11_and_emit(c, m);
                if (r < 0)
                        log_error_errno(r, "Failed to convert keymap data: %m");
        }

        return sd_bus_reply_method_return(m, NULL);
}