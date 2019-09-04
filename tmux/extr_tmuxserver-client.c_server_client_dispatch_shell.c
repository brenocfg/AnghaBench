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
struct client {int /*<<< orphan*/  peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_SHELL ; 
 char* _PATH_BSHELL ; 
 scalar_t__ areshell (char const*) ; 
 int /*<<< orphan*/  global_s_options ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  proc_kill_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
server_client_dispatch_shell(struct client *c)
{
	const char	*shell;

	shell = options_get_string(global_s_options, "default-shell");
	if (*shell == '\0' || areshell(shell))
		shell = _PATH_BSHELL;
	proc_send(c->peer, MSG_SHELL, -1, shell, strlen(shell) + 1);

	proc_kill_peer(c->peer);
}