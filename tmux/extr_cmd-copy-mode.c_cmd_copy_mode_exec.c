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
struct window_pane {int dummy; } ;
struct session {int dummy; } ;
struct cmdq_shared {int /*<<< orphan*/  mouse; } ;
struct TYPE_2__ {struct window_pane* wp; } ;
struct cmdq_item {TYPE_1__ target; struct client* client; struct cmdq_shared* shared; } ;
struct cmd {struct args* args; int /*<<< orphan*/ * entry; } ;
struct client {struct session* session; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 scalar_t__ args_has (struct args*,unsigned char) ; 
 int /*<<< orphan*/  cmd_clock_mode_entry ; 
 struct window_pane* cmd_mouse_pane (int /*<<< orphan*/ *,struct session**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_clock_mode ; 
 int /*<<< orphan*/  window_copy_mode ; 
 int /*<<< orphan*/  window_copy_pageup (struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_start_drag (struct client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_pane_set_mode (struct window_pane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct args*) ; 

__attribute__((used)) static enum cmd_retval
cmd_copy_mode_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmdq_shared	*shared = item->shared;
	struct client		*c = item->client;
	struct session		*s;
	struct window_pane	*wp = item->target.wp;

	if (args_has(args, 'M')) {
		if ((wp = cmd_mouse_pane(&shared->mouse, &s, NULL)) == NULL)
			return (CMD_RETURN_NORMAL);
		if (c == NULL || c->session != s)
			return (CMD_RETURN_NORMAL);
	}

	if (self->entry == &cmd_clock_mode_entry) {
		window_pane_set_mode(wp, &window_clock_mode, NULL, NULL);
		return (CMD_RETURN_NORMAL);
	}

	if (!window_pane_set_mode(wp, &window_copy_mode, NULL, args)) {
		if (args_has(args, 'M'))
			window_copy_start_drag(c, &shared->mouse);
	}
	if (args_has(self->args, 'u'))
		window_copy_pageup(wp, 0);

	return (CMD_RETURN_NORMAL);
}