#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * binding_mode_text; int /*<<< orphan*/ * binding_mode_bg; int /*<<< orphan*/ * binding_mode_border; int /*<<< orphan*/ * focused_separator; int /*<<< orphan*/ * focused_statusline; int /*<<< orphan*/ * focused_background; void* urgent_workspace_text; void* urgent_workspace_bg; void* urgent_workspace_border; void* inactive_workspace_text; void* inactive_workspace_bg; void* inactive_workspace_border; void* active_workspace_text; void* active_workspace_bg; void* active_workspace_border; void* focused_workspace_text; void* focused_workspace_bg; void* focused_workspace_border; void* separator; void* statusline; void* background; } ;
struct bar_config {int pango_markup; int workspace_buttons; int wrap_scroll; int strip_workspace_numbers; int strip_workspace_name; int binding_mode_indicator; int verbose; int status_padding; int status_edge_padding; int tray_padding; int /*<<< orphan*/  tray_bindings; TYPE_1__ colors; int /*<<< orphan*/  bindings; void* hidden_state; void* mode; int /*<<< orphan*/  modifier; int /*<<< orphan*/ * separator_symbol; scalar_t__ height; int /*<<< orphan*/ * font; int /*<<< orphan*/ * swaybar_command; void* position; int /*<<< orphan*/ * outputs; } ;

/* Variables and functions */
 struct bar_config* calloc (int,int) ; 
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  free_bar_config (struct bar_config*) ; 
 int /*<<< orphan*/  get_modifier_mask_by_name (char*) ; 
 void* strdup (char*) ; 
 void* strndup (char*,int) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 

struct bar_config *default_bar_config(void) {
	struct bar_config *bar = NULL;
	bar = calloc(1, sizeof(struct bar_config));
	if (!bar) {
		return NULL;
	}
	bar->outputs = NULL;
	bar->position = strdup("bottom");
	bar->pango_markup = false;
	bar->swaybar_command = NULL;
	bar->font = NULL;
	bar->height = 0;
	bar->workspace_buttons = true;
	bar->wrap_scroll = false;
	bar->separator_symbol = NULL;
	bar->strip_workspace_numbers = false;
	bar->strip_workspace_name = false;
	bar->binding_mode_indicator = true;
	bar->verbose = false;
	bar->modifier = get_modifier_mask_by_name("Mod4");
	bar->status_padding = 1;
	bar->status_edge_padding = 3;
	if (!(bar->mode = strdup("dock"))) {
	       goto cleanup;
	}
	if (!(bar->hidden_state = strdup("hide"))) {
		goto cleanup;
	}
	if (!(bar->bindings = create_list())) {
		goto cleanup;
	}
	// set default colors
	if (!(bar->colors.background = strndup("#000000ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.statusline = strndup("#ffffffff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.separator = strndup("#666666ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.focused_workspace_border = strndup("#4c7899ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.focused_workspace_bg = strndup("#285577ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.focused_workspace_text = strndup("#ffffffff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.active_workspace_border = strndup("#333333ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.active_workspace_bg = strndup("#5f676aff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.active_workspace_text = strndup("#ffffffff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.inactive_workspace_border = strndup("#333333ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.inactive_workspace_bg = strndup("#222222ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.inactive_workspace_text = strndup("#888888ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.urgent_workspace_border = strndup("#2f343aff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.urgent_workspace_bg = strndup("#900000ff", 9))) {
		goto cleanup;
	}
	if (!(bar->colors.urgent_workspace_text = strndup("#ffffffff", 9))) {
		goto cleanup;
	}
	// if the following colors stay undefined, they fall back to background,
	// statusline, separator and urgent_workspace_*.
	bar->colors.focused_background = NULL;
	bar->colors.focused_statusline = NULL;
	bar->colors.focused_separator = NULL;
	bar->colors.binding_mode_border = NULL;
	bar->colors.binding_mode_bg = NULL;
	bar->colors.binding_mode_text = NULL;

#if HAVE_TRAY
	bar->tray_padding = 2;
	wl_list_init(&bar->tray_bindings);
#endif

	return bar;
cleanup:
	free_bar_config(bar);
	return NULL;
}