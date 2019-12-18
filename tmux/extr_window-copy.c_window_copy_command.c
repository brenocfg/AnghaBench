#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct winlink {int dummy; } ;
struct window_mode_entry {int prefix; int /*<<< orphan*/  wp; struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int searchx; int searchy; int /*<<< orphan*/ * searchmark; } ;
struct window_copy_cmd_state {struct winlink* wl; struct session* s; struct client* c; struct mouse_event* m; struct args* args; struct window_mode_entry* wme; } ;
struct session {int dummy; } ;
struct mouse_event {int /*<<< orphan*/  b; scalar_t__ valid; } ;
struct client {int dummy; } ;
struct args {int argc; char** argv; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_3__ {int minargs; int maxargs; int (* f ) (struct window_copy_cmd_state*) ;int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_WHEEL (int /*<<< orphan*/ ) ; 
 int WINDOW_COPY_CMD_CANCEL ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 int WINDOW_COPY_CMD_REDRAW ; 
 size_t nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int stub1 (struct window_copy_cmd_state*) ; 
 int /*<<< orphan*/  window_copy_clear_marks (struct window_mode_entry*) ; 
 TYPE_1__* window_copy_cmd_table ; 
 int /*<<< orphan*/  window_copy_move_mouse (struct mouse_event*) ; 
 int /*<<< orphan*/  window_copy_redraw_screen (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_pane_reset_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_copy_command(struct window_mode_entry *wme, struct client *c,
    struct session *s, struct winlink *wl, struct args *args,
    struct mouse_event *m)
{
	struct window_copy_mode_data	*data = wme->data;
	struct window_copy_cmd_state	 cs;
	enum window_copy_cmd_action	 action;
	const char			*command;
	u_int				 i;

	if (args->argc == 0)
		return;
	command = args->argv[0];

	if (m != NULL && m->valid && !MOUSE_WHEEL(m->b))
		window_copy_move_mouse(m);

	cs.wme = wme;
	cs.args = args;
	cs.m = m;

	cs.c = c;
	cs.s = s;
	cs.wl = wl;

	action = WINDOW_COPY_CMD_NOTHING;
	for (i = 0; i < nitems(window_copy_cmd_table); i++) {
		if (strcmp(window_copy_cmd_table[i].command, command) == 0) {
			if (args->argc - 1 < window_copy_cmd_table[i].minargs ||
			    args->argc - 1 > window_copy_cmd_table[i].maxargs)
				break;
			action = window_copy_cmd_table[i].f (&cs);
			break;
		}
	}

	if (strncmp(command, "search-", 7) != 0 && data->searchmark != NULL) {
		window_copy_clear_marks(wme);
		if (action == WINDOW_COPY_CMD_NOTHING)
			action = WINDOW_COPY_CMD_REDRAW;
		data->searchx = data->searchy = -1;
	}
	wme->prefix = 1;

	if (action == WINDOW_COPY_CMD_CANCEL)
		window_pane_reset_mode(wme->wp);
	else if (action == WINDOW_COPY_CMD_REDRAW)
		window_copy_redraw_screen(wme);
}