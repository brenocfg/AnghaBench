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
struct client {int dummy; } ;

/* Variables and functions */
 int CMD_PARSE_QUIET ; 
 struct client* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TMUX_CONF ; 
 struct client* cfg_client ; 
 int /*<<< orphan*/  cfg_client_done ; 
 int /*<<< orphan*/  cfg_done ; 
 int /*<<< orphan*/ * cfg_file ; 
 int /*<<< orphan*/  cfg_item ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  cmdq_append (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_get_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* find_home () ; 
 int /*<<< orphan*/  load_cfg (int /*<<< orphan*/ *,struct client*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ **,char*,char const*) ; 

void
start_cfg(void)
{
	const char	*home;
	int		 flags = 0;
	struct client	*c;

	/*
	 * Configuration files are loaded without a client, so commands are run
	 * in the global queue with item->client NULL.
	 *
	 * However, we must block the initial client (but just the initial
	 * client) so that its command runs after the configuration is loaded.
	 * Because start_cfg() is called so early, we can be sure the client's
	 * command queue is currently empty and our callback will be at the
	 * front - we need to get in before MSG_COMMAND.
	 */
	cfg_client = c = TAILQ_FIRST(&clients);
	if (c != NULL) {
		cfg_item = cmdq_get_callback(cfg_client_done, NULL);
		cmdq_append(c, cfg_item);
	}

	if (cfg_file == NULL)
		load_cfg(TMUX_CONF, c, NULL, CMD_PARSE_QUIET, NULL);

	if (cfg_file == NULL && (home = find_home()) != NULL) {
		xasprintf(&cfg_file, "%s/.tmux.conf", home);
		flags = CMD_PARSE_QUIET;
	}
	if (cfg_file != NULL)
		load_cfg(cfg_file, c, NULL, flags, NULL);

	cmdq_append(NULL, cmdq_get_callback(cfg_done, NULL));
}