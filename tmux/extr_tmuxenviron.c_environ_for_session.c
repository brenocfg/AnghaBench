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
struct session {int id; int /*<<< orphan*/  environ; } ;
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  environ_copy (int /*<<< orphan*/ ,struct environ*) ; 
 struct environ* environ_create () ; 
 int /*<<< orphan*/  environ_set (struct environ*,char*,char*,char const*,...) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  global_options ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  socket_path ; 

struct environ *
environ_for_session(struct session *s, int no_TERM)
{
	struct environ	*env;
	const char	*value;
	int		 idx;

	env = environ_create();
	environ_copy(global_environ, env);
	if (s != NULL)
		environ_copy(s->environ, env);

	if (!no_TERM) {
		value = options_get_string(global_options, "default-terminal");
		environ_set(env, "TERM", "%s", value);
	}

	if (s != NULL)
		idx = s->id;
	else
		idx = -1;
	environ_set(env, "TMUX", "%s,%ld,%d", socket_path, (long)getpid(), idx);

	return (env);
}