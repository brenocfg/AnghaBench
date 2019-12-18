#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winlink {TYPE_2__* window; } ;
struct session {int dummy; } ;
struct TYPE_4__ {struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_1__ target; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 char* format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,struct winlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  options_set_number (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_status_window (TYPE_2__*) ; 
 int /*<<< orphan*/  window_set_name (TYPE_2__*,char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_rename_window_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	struct client	*c = cmd_find_client(item, NULL, 1);
	struct session	*s = item->target.s;
	struct winlink	*wl = item->target.wl;
	char		*newname;

	newname = format_single(item, args->argv[0], c, s, wl, NULL);
	window_set_name(wl->window, newname);
	options_set_number(wl->window->options, "automatic-rename", 0);

	server_status_window(wl->window);
	free(newname);

	return (CMD_RETURN_NORMAL);
}