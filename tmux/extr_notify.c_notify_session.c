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
struct session {int dummy; } ;
struct cmd_find_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_find_from_nothing (struct cmd_find_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_find_from_session (struct cmd_find_state*,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_add (char const*,struct cmd_find_state*,int /*<<< orphan*/ *,struct session*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ session_alive (struct session*) ; 

void
notify_session(const char *name, struct session *s)
{
	struct cmd_find_state	fs;

	if (session_alive(s))
		cmd_find_from_session(&fs, s, 0);
	else
		cmd_find_from_nothing(&fs, 0);
	notify_add(name, &fs, NULL, s, NULL, NULL);
}