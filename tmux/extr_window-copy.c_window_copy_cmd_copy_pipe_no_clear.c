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
struct winlink {int dummy; } ;
struct window_pane {int dummy; } ;
struct window_mode_entry {struct window_pane* wp; } ;
struct window_copy_cmd_state {TYPE_1__* args; struct winlink* wl; struct session* s; struct client* c; struct window_mode_entry* wme; } ;
struct session {int dummy; } ;
struct client {int dummy; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_2__ {int argc; char** argv; } ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 char* format_single (int /*<<< orphan*/ *,char*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  window_copy_copy_pipe (struct window_mode_entry*,struct session*,char*,char*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_copy_pipe_no_clear(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct client			*c = cs->c;
	struct session			*s = cs->s;
	struct winlink			*wl = cs->wl;
	struct window_pane		*wp = wme->wp;
	char				*command = NULL;
	char				*prefix = NULL;

	if (cs->args->argc == 3)
		prefix = format_single(NULL, cs->args->argv[2], c, s, wl, wp);

	if (s != NULL && *cs->args->argv[1] != '\0') {
		command = format_single(NULL, cs->args->argv[1], c, s, wl, wp);
		window_copy_copy_pipe(wme, s, prefix, command);
		free(command);
	}

	free(prefix);
	return (WINDOW_COPY_CMD_NOTHING);
}