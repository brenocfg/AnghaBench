#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct bar_config* binding_mode_text; struct bar_config* binding_mode_bg; struct bar_config* binding_mode_border; struct bar_config* urgent_workspace_text; struct bar_config* urgent_workspace_bg; struct bar_config* urgent_workspace_border; struct bar_config* inactive_workspace_text; struct bar_config* inactive_workspace_bg; struct bar_config* inactive_workspace_border; struct bar_config* active_workspace_text; struct bar_config* active_workspace_bg; struct bar_config* active_workspace_border; struct bar_config* focused_workspace_text; struct bar_config* focused_workspace_bg; struct bar_config* focused_workspace_border; struct bar_config* focused_separator; struct bar_config* focused_statusline; struct bar_config* focused_background; struct bar_config* separator; struct bar_config* statusline; struct bar_config* background; } ;
struct bar_config {scalar_t__ pid; TYPE_1__ colors; int /*<<< orphan*/  outputs; TYPE_2__* bindings; struct bar_config* separator_symbol; struct bar_config* font; struct bar_config* swaybar_command; struct bar_config* status_command; struct bar_config* hidden_state; struct bar_config* position; struct bar_config* mode; struct bar_config* id; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct bar_config*) ; 
 int /*<<< orphan*/  free_bar_binding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate_swaybar (scalar_t__) ; 

void free_bar_config(struct bar_config *bar) {
	if (!bar) {
		return;
	}
	free(bar->id);
	free(bar->mode);
	free(bar->position);
	free(bar->hidden_state);
	free(bar->status_command);
	free(bar->swaybar_command);
	free(bar->font);
	free(bar->separator_symbol);
	for (int i = 0; i < bar->bindings->length; i++) {
		free_bar_binding(bar->bindings->items[i]);
	}
	list_free(bar->bindings);
	list_free_items_and_destroy(bar->outputs);
	if (bar->pid != 0) {
		terminate_swaybar(bar->pid);
	}
	free(bar->colors.background);
	free(bar->colors.statusline);
	free(bar->colors.separator);
	free(bar->colors.focused_background);
	free(bar->colors.focused_statusline);
	free(bar->colors.focused_separator);
	free(bar->colors.focused_workspace_border);
	free(bar->colors.focused_workspace_bg);
	free(bar->colors.focused_workspace_text);
	free(bar->colors.active_workspace_border);
	free(bar->colors.active_workspace_bg);
	free(bar->colors.active_workspace_text);
	free(bar->colors.inactive_workspace_border);
	free(bar->colors.inactive_workspace_bg);
	free(bar->colors.inactive_workspace_text);
	free(bar->colors.urgent_workspace_border);
	free(bar->colors.urgent_workspace_bg);
	free(bar->colors.urgent_workspace_text);
	free(bar->colors.binding_mode_border);
	free(bar->colors.binding_mode_bg);
	free(bar->colors.binding_mode_text);
#if HAVE_TRAY
	list_free_items_and_destroy(bar->tray_outputs);
	free(bar->icon_theme);

	struct tray_binding *tray_bind = NULL, *tmp_tray_bind = NULL;
	wl_list_for_each_safe(tray_bind, tmp_tray_bind, &bar->tray_bindings, link) {
		wl_list_remove(&tray_bind->link);
		free(tray_bind);
	}
#endif
	free(bar);
}