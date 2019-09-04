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
struct winlink {TYPE_1__* window; } ;
struct session {struct options* options; } ;
struct options {int dummy; } ;
struct cmd_find_state {struct winlink* wl; struct session* s; } ;
struct args {int dummy; } ;
typedef  enum options_table_scope { ____Placeholder_options_table_scope } options_table_scope ;
struct TYPE_2__ {struct options* options; } ;

/* Variables and functions */
 int OPTIONS_TABLE_NONE ; 
 int OPTIONS_TABLE_SERVER ; 
 int OPTIONS_TABLE_SESSION ; 
 int OPTIONS_TABLE_WINDOW ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct options* global_options ; 
 struct options* global_s_options ; 
 struct options* global_w_options ; 
 int /*<<< orphan*/  xasprintf (char**,char*,...) ; 

enum options_table_scope
options_scope_from_flags(struct args *args, int window,
    struct cmd_find_state *fs, struct options **oo, char **cause)
{
	struct session	*s = fs->s;
	struct winlink	*wl = fs->wl;
	const char	*target= args_get(args, 't');

	if (args_has(args, 's')) {
		*oo = global_options;
		return (OPTIONS_TABLE_SERVER);
	}

	if (window || args_has(args, 'w')) {
		if (args_has(args, 'g')) {
			*oo = global_w_options;
			return (OPTIONS_TABLE_WINDOW);
		}
		if (wl == NULL) {
			if (target != NULL)
				xasprintf(cause, "no such window: %s", target);
			else
				xasprintf(cause, "no current window");
			return (OPTIONS_TABLE_NONE);
		}
		*oo = wl->window->options;
		return (OPTIONS_TABLE_WINDOW);
	} else {
		if (args_has(args, 'g')) {
			*oo = global_s_options;
			return (OPTIONS_TABLE_SESSION);
		}
		if (s == NULL) {
			if (target != NULL)
				xasprintf(cause, "no such session: %s", target);
			else
				xasprintf(cause, "no current session");
			return (OPTIONS_TABLE_NONE);
		}
		*oo = s->options;
		return (OPTIONS_TABLE_SESSION);
	}
}