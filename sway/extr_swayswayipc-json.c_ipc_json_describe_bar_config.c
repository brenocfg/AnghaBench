#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* background; char const* statusline; char const* separator; char const* focused_background; char const* focused_statusline; char const* focused_separator; char const* focused_workspace_border; char const* focused_workspace_bg; char const* focused_workspace_text; char const* inactive_workspace_border; char const* inactive_workspace_bg; char const* inactive_workspace_text; char const* active_workspace_border; char const* active_workspace_bg; char const* active_workspace_text; char const* urgent_workspace_border; char const* urgent_workspace_bg; char const* urgent_workspace_text; char const* binding_mode_border; char const* binding_mode_bg; char const* binding_mode_text; } ;
struct TYPE_8__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; } ;
struct bar_config {char const* id; char const* mode; char const* hidden_state; char const* position; char const* status_command; char const* font; char const* separator_symbol; TYPE_2__* outputs; TYPE_1__* bindings; TYPE_4__ colors; int /*<<< orphan*/  pango_markup; int /*<<< orphan*/  verbose; int /*<<< orphan*/  binding_mode_indicator; int /*<<< orphan*/  strip_workspace_name; int /*<<< orphan*/  strip_workspace_numbers; int /*<<< orphan*/  workspace_buttons; int /*<<< orphan*/  wrap_scroll; int /*<<< orphan*/  status_edge_padding; int /*<<< orphan*/  status_padding; int /*<<< orphan*/  height; TYPE_3__ gaps; } ;
struct bar_binding {char const* command; int /*<<< orphan*/  release; int /*<<< orphan*/  button; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_10__ {char const* font; } ;
struct TYPE_7__ {scalar_t__ length; char** items; } ;
struct TYPE_6__ {scalar_t__ length; struct bar_binding** items; } ;

/* Variables and functions */
 TYPE_5__* config ; 
 int /*<<< orphan*/  event_to_x11_button (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/ * json_object_new_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/ * json_object_new_string (char const*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (struct bar_config*,char*) ; 

json_object *ipc_json_describe_bar_config(struct bar_config *bar) {
	if (!sway_assert(bar, "Bar must not be NULL")) {
		return NULL;
	}

	json_object *json = json_object_new_object();
	json_object_object_add(json, "id", json_object_new_string(bar->id));
	json_object_object_add(json, "mode", json_object_new_string(bar->mode));
	json_object_object_add(json, "hidden_state",
			json_object_new_string(bar->hidden_state));
	json_object_object_add(json, "position",
			json_object_new_string(bar->position));
	json_object_object_add(json, "status_command", bar->status_command ?
			json_object_new_string(bar->status_command) : NULL);
	json_object_object_add(json, "font",
			json_object_new_string((bar->font) ? bar->font : config->font));

	json_object *gaps = json_object_new_object();
	json_object_object_add(gaps, "top",
			json_object_new_int(bar->gaps.top));
	json_object_object_add(gaps, "right",
			json_object_new_int(bar->gaps.right));
	json_object_object_add(gaps, "bottom",
			json_object_new_int(bar->gaps.bottom));
	json_object_object_add(gaps, "left",
			json_object_new_int(bar->gaps.left));
	json_object_object_add(json, "gaps", gaps);

	if (bar->separator_symbol) {
		json_object_object_add(json, "separator_symbol",
				json_object_new_string(bar->separator_symbol));
	}
	json_object_object_add(json, "bar_height",
			json_object_new_int(bar->height));
	json_object_object_add(json, "status_padding",
			json_object_new_int(bar->status_padding));
	json_object_object_add(json, "status_edge_padding",
			json_object_new_int(bar->status_edge_padding));
	json_object_object_add(json, "wrap_scroll",
			json_object_new_boolean(bar->wrap_scroll));
	json_object_object_add(json, "workspace_buttons",
			json_object_new_boolean(bar->workspace_buttons));
	json_object_object_add(json, "strip_workspace_numbers",
			json_object_new_boolean(bar->strip_workspace_numbers));
	json_object_object_add(json, "strip_workspace_name",
			json_object_new_boolean(bar->strip_workspace_name));
	json_object_object_add(json, "binding_mode_indicator",
			json_object_new_boolean(bar->binding_mode_indicator));
	json_object_object_add(json, "verbose",
			json_object_new_boolean(bar->verbose));
	json_object_object_add(json, "pango_markup",
			json_object_new_boolean(bar->pango_markup));

	json_object *colors = json_object_new_object();
	json_object_object_add(colors, "background",
			json_object_new_string(bar->colors.background));
	json_object_object_add(colors, "statusline",
			json_object_new_string(bar->colors.statusline));
	json_object_object_add(colors, "separator",
			json_object_new_string(bar->colors.separator));

	if (bar->colors.focused_background) {
		json_object_object_add(colors, "focused_background",
				json_object_new_string(bar->colors.focused_background));
	} else {
		json_object_object_add(colors, "focused_background",
				json_object_new_string(bar->colors.background));
	}

	if (bar->colors.focused_statusline) {
		json_object_object_add(colors, "focused_statusline",
				json_object_new_string(bar->colors.focused_statusline));
	} else {
		json_object_object_add(colors, "focused_statusline",
				json_object_new_string(bar->colors.statusline));
	}

	if (bar->colors.focused_separator) {
		json_object_object_add(colors, "focused_separator",
				json_object_new_string(bar->colors.focused_separator));
	} else {
		json_object_object_add(colors, "focused_separator",
				json_object_new_string(bar->colors.separator));
	}

	json_object_object_add(colors, "focused_workspace_border",
			json_object_new_string(bar->colors.focused_workspace_border));
	json_object_object_add(colors, "focused_workspace_bg",
			json_object_new_string(bar->colors.focused_workspace_bg));
	json_object_object_add(colors, "focused_workspace_text",
			json_object_new_string(bar->colors.focused_workspace_text));

	json_object_object_add(colors, "inactive_workspace_border",
			json_object_new_string(bar->colors.inactive_workspace_border));
	json_object_object_add(colors, "inactive_workspace_bg",
			json_object_new_string(bar->colors.inactive_workspace_bg));
	json_object_object_add(colors, "inactive_workspace_text",
			json_object_new_string(bar->colors.inactive_workspace_text));

	json_object_object_add(colors, "active_workspace_border",
			json_object_new_string(bar->colors.active_workspace_border));
	json_object_object_add(colors, "active_workspace_bg",
			json_object_new_string(bar->colors.active_workspace_bg));
	json_object_object_add(colors, "active_workspace_text",
			json_object_new_string(bar->colors.active_workspace_text));

	json_object_object_add(colors, "urgent_workspace_border",
			json_object_new_string(bar->colors.urgent_workspace_border));
	json_object_object_add(colors, "urgent_workspace_bg",
			json_object_new_string(bar->colors.urgent_workspace_bg));
	json_object_object_add(colors, "urgent_workspace_text",
			json_object_new_string(bar->colors.urgent_workspace_text));

	if (bar->colors.binding_mode_border) {
		json_object_object_add(colors, "binding_mode_border",
				json_object_new_string(bar->colors.binding_mode_border));
	} else {
		json_object_object_add(colors, "binding_mode_border",
				json_object_new_string(bar->colors.urgent_workspace_border));
	}

	if (bar->colors.binding_mode_bg) {
		json_object_object_add(colors, "binding_mode_bg",
				json_object_new_string(bar->colors.binding_mode_bg));
	} else {
		json_object_object_add(colors, "binding_mode_bg",
				json_object_new_string(bar->colors.urgent_workspace_bg));
	}

	if (bar->colors.binding_mode_text) {
		json_object_object_add(colors, "binding_mode_text",
				json_object_new_string(bar->colors.binding_mode_text));
	} else {
		json_object_object_add(colors, "binding_mode_text",
				json_object_new_string(bar->colors.urgent_workspace_text));
	}

	json_object_object_add(json, "colors", colors);

	if (bar->bindings->length > 0) {
		json_object *bindings = json_object_new_array();
		for (int i = 0; i < bar->bindings->length; ++i) {
			struct bar_binding *binding = bar->bindings->items[i];
			json_object *bind = json_object_new_object();
			json_object_object_add(bind, "input_code",
					json_object_new_int(event_to_x11_button(binding->button)));
			json_object_object_add(bind, "event_code",
					json_object_new_int(binding->button));
			json_object_object_add(bind, "command",
					json_object_new_string(binding->command));
			json_object_object_add(bind, "release",
					json_object_new_boolean(binding->release));
			json_object_array_add(bindings, bind);
		}
		json_object_object_add(json, "bindings", bindings);
	}

	// Add outputs if defined
	if (bar->outputs && bar->outputs->length > 0) {
		json_object *outputs = json_object_new_array();
		for (int i = 0; i < bar->outputs->length; ++i) {
			const char *name = bar->outputs->items[i];
			json_object_array_add(outputs, json_object_new_string(name));
		}
		json_object_object_add(json, "outputs", outputs);
	}
#if HAVE_TRAY
	// Add tray outputs if defined
	if (bar->tray_outputs && bar->tray_outputs->length > 0) {
		json_object *tray_outputs = json_object_new_array();
		for (int i = 0; i < bar->tray_outputs->length; ++i) {
			const char *name = bar->tray_outputs->items[i];
			json_object_array_add(tray_outputs, json_object_new_string(name));
		}
		json_object_object_add(json, "tray_outputs", tray_outputs);
	}

	json_object *tray_bindings = json_object_new_array();
	struct tray_binding *tray_bind = NULL;
	wl_list_for_each(tray_bind, &bar->tray_bindings, link) {
		json_object *bind = json_object_new_object();
		json_object_object_add(bind, "input_code",
				json_object_new_int(event_to_x11_button(tray_bind->button)));
		json_object_object_add(bind, "event_code",
				json_object_new_int(tray_bind->button));
		json_object_object_add(bind, "command",
				json_object_new_string(tray_bind->command));
		json_object_array_add(tray_bindings, bind);
	}
	if (json_object_array_length(tray_bindings) > 0) {
		json_object_object_add(json, "tray_bindings", tray_bindings);
	} else {
		json_object_put(tray_bindings);
	}

	if (bar->icon_theme) {
		json_object_object_add(json, "icon_theme",
				json_object_new_string(bar->icon_theme));
	}

	json_object_object_add(json, "tray_padding",
			json_object_new_int(bar->tray_padding));
#endif
	return json;
}