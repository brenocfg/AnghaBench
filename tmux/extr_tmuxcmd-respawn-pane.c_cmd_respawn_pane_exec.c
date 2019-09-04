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
struct window_pane {int /*<<< orphan*/  window; int /*<<< orphan*/  flags; } ;
struct spawn_context {int idx; int /*<<< orphan*/  environ; int /*<<< orphan*/  flags; int /*<<< orphan*/  cwd; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; int /*<<< orphan*/ * name; int /*<<< orphan*/ * lc; struct window_pane* wp0; struct winlink* wl; struct session* s; struct cmdq_item* item; } ;
struct session {int dummy; } ;
struct TYPE_2__ {struct window_pane* wp; struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_1__ target; } ;
struct cmd {struct args* args; } ;
struct args_value {int dummy; } ;
struct args {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  SPAWN_KILL ; 
 int /*<<< orphan*/  SPAWN_RESPAWN ; 
 char* args_first_value (struct args*,char,struct args_value**) ; 
 int /*<<< orphan*/  args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 char* args_next_value (struct args_value**) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  environ_create () ; 
 int /*<<< orphan*/  environ_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ_put (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct spawn_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_status_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spawn_pane (struct spawn_context*,char**) ; 

__attribute__((used)) static enum cmd_retval
cmd_respawn_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct spawn_context	 sc;
	struct session		*s = item->target.s;
	struct winlink		*wl = item->target.wl;
	struct window_pane	*wp = item->target.wp;
	char			*cause = NULL;
	const char		*add;
	struct args_value	*value;

	memset(&sc, 0, sizeof sc);
	sc.item = item;
	sc.s = s;
	sc.wl = wl;

	sc.wp0 = wp;
	sc.lc = NULL;

	sc.name = NULL;
	sc.argc = args->argc;
	sc.argv = args->argv;
	sc.environ = environ_create();

	add = args_first_value(args, 'e', &value);
	while (add != NULL) {
		environ_put(sc.environ, add);
		add = args_next_value(&value);
	}

	sc.idx = -1;
	sc.cwd = args_get(args, 'c');

	sc.flags = SPAWN_RESPAWN;
	if (args_has(args, 'k'))
		sc.flags |= SPAWN_KILL;

	if (spawn_pane(&sc, &cause) == NULL) {
		cmdq_error(item, "respawn pane failed: %s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}

	wp->flags |= PANE_REDRAW;
	server_status_window(wp->window);

	environ_free(sc.environ);
	return (CMD_RETURN_NORMAL);
}