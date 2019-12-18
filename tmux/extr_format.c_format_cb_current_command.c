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
struct window_pane {int /*<<< orphan*/ * shell; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; int /*<<< orphan*/  tty; int /*<<< orphan*/  fd; } ;
struct format_tree {struct window_pane* wp; } ;
struct format_entry {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 char* cmd_stringify_argv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* osdep_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_window_name (char*) ; 
 char* xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
format_cb_current_command(struct format_tree *ft, struct format_entry *fe)
{
	struct window_pane	*wp = ft->wp;
	char			*cmd;

	if (wp == NULL || wp->shell == NULL)
		return;

	cmd = osdep_get_name(wp->fd, wp->tty);
	if (cmd == NULL || *cmd == '\0') {
		free(cmd);
		cmd = cmd_stringify_argv(wp->argc, wp->argv);
		if (cmd == NULL || *cmd == '\0') {
			free(cmd);
			cmd = xstrdup(wp->shell);
		}
	}
	fe->value = parse_window_name(cmd);
	free(cmd);
}