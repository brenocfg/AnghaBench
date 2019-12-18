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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int /*<<< orphan*/  lineflag; } ;
struct window_copy_cmd_state {struct mouse_event* m; struct client* c; struct window_mode_entry* wme; } ;
struct mouse_event {int dummy; } ;
struct client {int dummy; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_SEL_NONE ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 int WINDOW_COPY_CMD_REDRAW ; 
 int /*<<< orphan*/  window_copy_start_drag (struct client*,struct mouse_event*) ; 
 int /*<<< orphan*/  window_copy_start_selection (struct window_mode_entry*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_begin_selection(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct client			*c = cs->c;
	struct mouse_event		*m = cs->m;
	struct window_copy_mode_data	*data = wme->data;

	if (m != NULL) {
		window_copy_start_drag(c, m);
		return (WINDOW_COPY_CMD_NOTHING);
	}

	data->lineflag = LINE_SEL_NONE;
	window_copy_start_selection(wme);
	return (WINDOW_COPY_CMD_REDRAW);
}