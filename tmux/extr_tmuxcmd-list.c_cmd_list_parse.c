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
typedef  int /*<<< orphan*/  u_int ;
struct cmd_list {int references; int /*<<< orphan*/  list; } ;
struct cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cmd*,int /*<<< orphan*/ ) ; 
 char** cmd_copy_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd* cmd_parse (int,char**,char const*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  qentry ; 
 size_t strlen (char*) ; 
 struct cmd_list* xcalloc (int,int) ; 

struct cmd_list *
cmd_list_parse(int argc, char **argv, const char *file, u_int line,
    char **cause)
{
	struct cmd_list	*cmdlist;
	struct cmd	*cmd;
	int		 i, lastsplit;
	size_t		 arglen, new_argc;
	char	       **copy_argv, **new_argv;

	copy_argv = cmd_copy_argv(argc, argv);

	cmdlist = xcalloc(1, sizeof *cmdlist);
	cmdlist->references = 1;
	TAILQ_INIT(&cmdlist->list);

	lastsplit = 0;
	for (i = 0; i < argc; i++) {
		arglen = strlen(copy_argv[i]);
		if (arglen == 0 || copy_argv[i][arglen - 1] != ';')
			continue;
		copy_argv[i][arglen - 1] = '\0';

		if (arglen > 1 && copy_argv[i][arglen - 2] == '\\') {
			copy_argv[i][arglen - 2] = ';';
			continue;
		}

		new_argc = i - lastsplit;
		new_argv = copy_argv + lastsplit;
		if (arglen != 1)
			new_argc++;

		cmd = cmd_parse(new_argc, new_argv, file, line, cause);
		if (cmd == NULL)
			goto bad;
		TAILQ_INSERT_TAIL(&cmdlist->list, cmd, qentry);

		lastsplit = i + 1;
	}

	if (lastsplit != argc) {
		cmd = cmd_parse(argc - lastsplit, copy_argv + lastsplit,
		    file, line, cause);
		if (cmd == NULL)
			goto bad;
		TAILQ_INSERT_TAIL(&cmdlist->list, cmd, qentry);
	}

	cmd_free_argv(argc, copy_argv);
	return (cmdlist);

bad:
	cmd_list_free(cmdlist);
	cmd_free_argv(argc, copy_argv);
	return (NULL);
}