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
struct window {int dummy; } ;
struct session {int dummy; } ;
struct cmd_find_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_find_from_session_window (struct cmd_find_state*,struct session*,struct window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_add (char const*,struct cmd_find_state*,int /*<<< orphan*/ *,struct session*,struct window*,int /*<<< orphan*/ *) ; 

void
notify_session_window(const char *name, struct session *s, struct window *w)
{
	struct cmd_find_state	fs;

	cmd_find_from_session_window(&fs, s, w, 0);
	notify_add(name, &fs, NULL, s, w, NULL);
}