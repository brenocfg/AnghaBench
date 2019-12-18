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
struct window {TYPE_1__* active; } ;
struct TYPE_2__ {char* shell; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 char* cmd_stringify_argv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* parse_window_name (char*) ; 

char *
default_window_name(struct window *w)
{
	char    *cmd, *s;

	cmd = cmd_stringify_argv(w->active->argc, w->active->argv);
	if (cmd != NULL && *cmd != '\0')
		s = parse_window_name(cmd);
	else
		s = parse_window_name(w->active->shell);
	free(cmd);
	return (s);
}