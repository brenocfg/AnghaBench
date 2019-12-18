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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {char* searchstr; int searchx; int searchy; int cx; int cy; int /*<<< orphan*/  searchtype; int /*<<< orphan*/  searcho; int /*<<< orphan*/  oy; } ;
struct window_copy_cmd_state {TYPE_1__* args; struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_2__ {char** argv; } ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 int WINDOW_COPY_CMD_REDRAW ; 
 int /*<<< orphan*/  WINDOW_COPY_SEARCHDOWN ; 
 int /*<<< orphan*/  WINDOW_COPY_SEARCHUP ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  window_copy_clear_marks (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_search_down (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_search_up (struct window_mode_entry*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_search_forward_incremental(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct window_copy_mode_data	*data = wme->data;
	const char			*argument = cs->args->argv[1];
	const char			*ss = data->searchstr;
	char				 prefix;
	enum window_copy_cmd_action	 action = WINDOW_COPY_CMD_NOTHING;

	prefix = *argument++;
	if (data->searchx == -1 || data->searchy == -1) {
		data->searchx = data->cx;
		data->searchy = data->cy;
		data->searcho = data->oy;
	} else if (ss != NULL && strcmp(argument, ss) != 0) {
		data->cx = data->searchx;
		data->cy = data->searchy;
		data->oy = data->searcho;
		action = WINDOW_COPY_CMD_REDRAW;
	}
	if (*argument == '\0') {
		window_copy_clear_marks(wme);
		return (WINDOW_COPY_CMD_REDRAW);
	}
	switch (prefix) {
	case '=':
	case '+':
		data->searchtype = WINDOW_COPY_SEARCHDOWN;
		free(data->searchstr);
		data->searchstr = xstrdup(argument);
		if (!window_copy_search_down(wme)) {
			window_copy_clear_marks(wme);
			return (WINDOW_COPY_CMD_REDRAW);
		}
		break;
	case '-':
		data->searchtype = WINDOW_COPY_SEARCHUP;
		free(data->searchstr);
		data->searchstr = xstrdup(argument);
		if (!window_copy_search_up(wme)) {
			window_copy_clear_marks(wme);
			return (WINDOW_COPY_CMD_REDRAW);
		}
	}
	return (action);
}