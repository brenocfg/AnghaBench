#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* text; void* background; void* border; } ;
struct TYPE_10__ {void* text; void* background; void* border; } ;
struct TYPE_9__ {void* text; void* background; void* border; } ;
struct TYPE_8__ {void* text; void* background; void* border; } ;
struct TYPE_7__ {void* text; void* background; void* border; } ;
struct TYPE_12__ {TYPE_5__ binding_mode; TYPE_4__ urgent_workspace; TYPE_3__ inactive_workspace; TYPE_2__ active_workspace; TYPE_1__ focused_workspace; void* focused_separator; void* focused_statusline; void* focused_background; void* separator; void* statusline; void* background; } ;
struct swaybar_config {TYPE_6__ colors; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 void* parse_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipc_parse_colors(
		struct swaybar_config *config, json_object *colors) {
	json_object *background, *statusline, *separator;
	json_object *focused_background, *focused_statusline, *focused_separator;
	json_object *focused_workspace_border, *focused_workspace_bg, *focused_workspace_text;
	json_object *inactive_workspace_border, *inactive_workspace_bg, *inactive_workspace_text;
	json_object *active_workspace_border, *active_workspace_bg, *active_workspace_text;
	json_object *urgent_workspace_border, *urgent_workspace_bg, *urgent_workspace_text;
	json_object *binding_mode_border, *binding_mode_bg, *binding_mode_text;
	json_object_object_get_ex(colors, "background", &background);
	json_object_object_get_ex(colors, "statusline", &statusline);
	json_object_object_get_ex(colors, "separator", &separator);
	json_object_object_get_ex(colors, "focused_background", &focused_background);
	json_object_object_get_ex(colors, "focused_statusline", &focused_statusline);
	json_object_object_get_ex(colors, "focused_separator", &focused_separator);
	json_object_object_get_ex(colors, "focused_workspace_border", &focused_workspace_border);
	json_object_object_get_ex(colors, "focused_workspace_bg", &focused_workspace_bg);
	json_object_object_get_ex(colors, "focused_workspace_text", &focused_workspace_text);
	json_object_object_get_ex(colors, "active_workspace_border", &active_workspace_border);
	json_object_object_get_ex(colors, "active_workspace_bg", &active_workspace_bg);
	json_object_object_get_ex(colors, "active_workspace_text", &active_workspace_text);
	json_object_object_get_ex(colors, "inactive_workspace_border", &inactive_workspace_border);
	json_object_object_get_ex(colors, "inactive_workspace_bg", &inactive_workspace_bg);
	json_object_object_get_ex(colors, "inactive_workspace_text", &inactive_workspace_text);
	json_object_object_get_ex(colors, "urgent_workspace_border", &urgent_workspace_border);
	json_object_object_get_ex(colors, "urgent_workspace_bg", &urgent_workspace_bg);
	json_object_object_get_ex(colors, "urgent_workspace_text", &urgent_workspace_text);
	json_object_object_get_ex(colors, "binding_mode_border", &binding_mode_border);
	json_object_object_get_ex(colors, "binding_mode_bg", &binding_mode_bg);
	json_object_object_get_ex(colors, "binding_mode_text", &binding_mode_text);
	if (background) {
		config->colors.background = parse_color(
				json_object_get_string(background));
	}
	if (statusline) {
		config->colors.statusline = parse_color(
				json_object_get_string(statusline));
	}
	if (separator) {
		config->colors.separator = parse_color(
				json_object_get_string(separator));
	}
	if (focused_background) {
		config->colors.focused_background = parse_color(
				json_object_get_string(focused_background));
	}
	if (focused_statusline) {
		config->colors.focused_statusline = parse_color(
				json_object_get_string(focused_statusline));
	}
	if (focused_separator) {
		config->colors.focused_separator = parse_color(
				json_object_get_string(focused_separator));
	}
	if (focused_workspace_border) {
		config->colors.focused_workspace.border = parse_color(
				json_object_get_string(focused_workspace_border));
	}
	if (focused_workspace_bg) {
		config->colors.focused_workspace.background = parse_color(
				json_object_get_string(focused_workspace_bg));
	}
	if (focused_workspace_text) {
		config->colors.focused_workspace.text = parse_color(
				json_object_get_string(focused_workspace_text));
	}
	if (active_workspace_border) {
		config->colors.active_workspace.border = parse_color(
				json_object_get_string(active_workspace_border));
	}
	if (active_workspace_bg) {
		config->colors.active_workspace.background = parse_color(
				json_object_get_string(active_workspace_bg));
	}
	if (active_workspace_text) {
		config->colors.active_workspace.text = parse_color(
				json_object_get_string(active_workspace_text));
	}
	if (inactive_workspace_border) {
		config->colors.inactive_workspace.border = parse_color(
				json_object_get_string(inactive_workspace_border));
	}
	if (inactive_workspace_bg) {
		config->colors.inactive_workspace.background = parse_color(
				json_object_get_string(inactive_workspace_bg));
	}
	if (inactive_workspace_text) {
		config->colors.inactive_workspace.text = parse_color(
				json_object_get_string(inactive_workspace_text));
	}
	if (urgent_workspace_border) {
		config->colors.urgent_workspace.border = parse_color(
				json_object_get_string(urgent_workspace_border));
	}
	if (urgent_workspace_bg) {
		config->colors.urgent_workspace.background = parse_color(
				json_object_get_string(urgent_workspace_bg));
	}
	if (urgent_workspace_text) {
		config->colors.urgent_workspace.text = parse_color(
				json_object_get_string(urgent_workspace_text));
	}
	if (binding_mode_border) {
		config->colors.binding_mode.border = parse_color(
				json_object_get_string(binding_mode_border));
	}
	if (binding_mode_bg) {
		config->colors.binding_mode.background = parse_color(
				json_object_get_string(binding_mode_bg));
	}
	if (binding_mode_text) {
		config->colors.binding_mode.text = parse_color(
				json_object_get_string(binding_mode_text));
	}
}