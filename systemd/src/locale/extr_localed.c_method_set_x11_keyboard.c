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
struct TYPE_14__ {char const* x11_layout; char const* x11_model; char const* x11_variant; char const* x11_options; int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SD_BUS_ERROR_FAILED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* empty_to_null (char const*) ; 
 scalar_t__ free_and_strdup (char const**,char const*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_emit_properties_changed (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,char const**,char const**,char const**,int*,int*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strempty (char const*) ; 
 scalar_t__ streq_ptr (char const*,char const*) ; 
 int /*<<< orphan*/  string_is_safe (char const*) ; 
 int verify_xkb_rmlvo (char const*,char const*,char const*,char const*) ; 
 int x11_convert_to_vconsole_and_emit (TYPE_1__*,TYPE_1__*) ; 
 int x11_read_data (TYPE_1__*,TYPE_1__*) ; 
 int x11_write_data (TYPE_1__*) ; 

__attribute__((used)) static int method_set_x11_keyboard(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        Context *c = userdata;
        const char *layout, *model, *variant, *options;
        int convert, interactive, r;

        assert(m);
        assert(c);

        r = sd_bus_message_read(m, "ssssbb", &layout, &model, &variant, &options, &convert, &interactive);
        if (r < 0)
                return r;

        layout = empty_to_null(layout);
        model = empty_to_null(model);
        variant = empty_to_null(variant);
        options = empty_to_null(options);

        r = x11_read_data(c, m);
        if (r < 0) {
                log_error_errno(r, "Failed to read x11 keyboard layout data: %m");
                return sd_bus_error_setf(error, SD_BUS_ERROR_FAILED, "Failed to read x11 keyboard layout data");
        }

        if (streq_ptr(layout, c->x11_layout) &&
            streq_ptr(model, c->x11_model) &&
            streq_ptr(variant, c->x11_variant) &&
            streq_ptr(options, c->x11_options))
                return sd_bus_reply_method_return(m, NULL);

        if ((layout && !string_is_safe(layout)) ||
            (model && !string_is_safe(model)) ||
            (variant && !string_is_safe(variant)) ||
            (options && !string_is_safe(options)))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Received invalid keyboard data");

        r = verify_xkb_rmlvo(model, layout, variant, options);
        if (r < 0) {
                log_error_errno(r, "Cannot compile XKB keymap for new x11 keyboard layout ('%s' / '%s' / '%s' / '%s'): %m",
                                strempty(model), strempty(layout), strempty(variant), strempty(options));

                if (r == -EOPNOTSUPP)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Local keyboard configuration not supported on this system.");

                return sd_bus_error_set(error, SD_BUS_ERROR_INVALID_ARGS, "Specified keymap cannot be compiled, refusing as invalid.");
        }

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

        if (free_and_strdup(&c->x11_layout, layout) < 0 ||
            free_and_strdup(&c->x11_model, model) < 0 ||
            free_and_strdup(&c->x11_variant, variant) < 0 ||
            free_and_strdup(&c->x11_options, options) < 0)
                return -ENOMEM;

        r = x11_write_data(c);
        if (r < 0) {
                log_error_errno(r, "Failed to set X11 keyboard layout: %m");
                return sd_bus_error_set_errnof(error, r, "Failed to set X11 keyboard layout: %m");
        }

        log_info("Changed X11 keyboard layout to '%s' model '%s' variant '%s' options '%s'",
                 strempty(c->x11_layout),
                 strempty(c->x11_model),
                 strempty(c->x11_variant),
                 strempty(c->x11_options));

        (void) sd_bus_emit_properties_changed(
                        sd_bus_message_get_bus(m),
                        "/org/freedesktop/locale1",
                        "org.freedesktop.locale1",
                        "X11Layout", "X11Model", "X11Variant", "X11Options", NULL);

        if (convert) {
                r = x11_convert_to_vconsole_and_emit(c, m);
                if (r < 0)
                        log_error_errno(r, "Failed to convert keymap data: %m");
        }

        return sd_bus_reply_method_return(m, NULL);
}