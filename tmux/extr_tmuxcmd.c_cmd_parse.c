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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int lower; int upper; int /*<<< orphan*/  template; } ;
struct cmd_entry {char* alias; char* name; char* usage; TYPE_1__ args; } ;
struct cmd {int /*<<< orphan*/  line; int /*<<< orphan*/  file; struct args* args; struct cmd_entry const* entry; } ;
struct args {int argc; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  args_free (struct args*) ; 
 struct args* args_parse (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_log_argv (int,char**,char*) ; 
 struct cmd_entry** cmd_table ; 
 scalar_t__ cmd_try_alias (int*,char***) ; 
 int /*<<< orphan*/ * server_proc ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlcat (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,...) ; 
 struct cmd* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct cmd *
cmd_parse(int argc, char **argv, const char *file, u_int line, char **cause)
{
	const char		*name;
	const struct cmd_entry **entryp, *entry;
	struct cmd		*cmd;
	struct args		*args;
	char			 s[BUFSIZ];
	int			 ambiguous, allocated = 0;

	*cause = NULL;
	if (argc == 0) {
		xasprintf(cause, "no command");
		return (NULL);
	}
	name = argv[0];

retry:
	ambiguous = 0;
	entry = NULL;
	for (entryp = cmd_table; *entryp != NULL; entryp++) {
		if ((*entryp)->alias != NULL &&
		    strcmp((*entryp)->alias, argv[0]) == 0) {
			ambiguous = 0;
			entry = *entryp;
			break;
		}

		if (strncmp((*entryp)->name, argv[0], strlen(argv[0])) != 0)
			continue;
		if (entry != NULL)
			ambiguous = 1;
		entry = *entryp;

		/* Bail now if an exact match. */
		if (strcmp(entry->name, argv[0]) == 0)
			break;
	}
	if ((ambiguous || entry == NULL) &&
	    server_proc != NULL &&
	    !allocated &&
	    cmd_try_alias(&argc, &argv) == 0) {
		allocated = 1;
		goto retry;
	}
	if (ambiguous)
		goto ambiguous;
	if (entry == NULL) {
		xasprintf(cause, "unknown command: %s", name);
		return (NULL);
	}
	cmd_log_argv(argc, argv, entry->name);

	args = args_parse(entry->args.template, argc, argv);
	if (args == NULL)
		goto usage;
	if (entry->args.lower != -1 && args->argc < entry->args.lower)
		goto usage;
	if (entry->args.upper != -1 && args->argc > entry->args.upper)
		goto usage;

	cmd = xcalloc(1, sizeof *cmd);
	cmd->entry = entry;
	cmd->args = args;

	if (file != NULL)
		cmd->file = xstrdup(file);
	cmd->line = line;

	if (allocated)
		cmd_free_argv(argc, argv);
	return (cmd);

ambiguous:
	*s = '\0';
	for (entryp = cmd_table; *entryp != NULL; entryp++) {
		if (strncmp((*entryp)->name, argv[0], strlen(argv[0])) != 0)
			continue;
		if (strlcat(s, (*entryp)->name, sizeof s) >= sizeof s)
			break;
		if (strlcat(s, ", ", sizeof s) >= sizeof s)
			break;
	}
	s[strlen(s) - 2] = '\0';
	xasprintf(cause, "ambiguous command: %s, could be: %s", name, s);
	return (NULL);

usage:
	if (args != NULL)
		args_free(args);
	xasprintf(cause, "usage: %s %s", entry->name, entry->usage);
	return (NULL);
}