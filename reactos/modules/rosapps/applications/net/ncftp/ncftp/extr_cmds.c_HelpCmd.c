#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmdnames ;
struct TYPE_9__ {char* name; int flags; } ;
typedef  TYPE_1__* CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetCommandByName (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintCmdHelp (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintCmdUsage (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 TYPE_1__* gCommands ; 
 int gNumCommands ; 
 int /*<<< orphan*/  gUnusedArg ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  iscntrl (int) ; 
 TYPE_1__* kAmbiguousCommand ; 
 int kCmdHidden ; 
 TYPE_1__* kNoCommand ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
HelpCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	CommandPtr c;
	int showall = 0, helpall = 0;
	int i, j, k, n;
	int nRows, nCols;
	int nCmds2Print;
	int screenColumns;
	int len, widestName;
	char *cp, spec[16];
	const char *cmdnames[64];

	ARGSUSED(gUnusedArg);
	assert(gNumCommands < (sizeof(cmdnames) / sizeof(char *)));
	if (argc == 2) {
		showall = (strcmp(argv[1], "showall") == 0);
		helpall = (strcmp(argv[1], "helpall") == 0);
	}
	if (argc == 1 || showall) {
		(void) printf("\
Commands may be abbreviated.  'help showall' shows hidden and unsupported \n\
commands.  'help <command>' gives a brief description of <command>.\n\n");

		/* First, see how many commands we will be printing to the screen.
		 * Unless 'showall' was given, we won't be printing the hidden
		 * (i.e. not very useful to the end-user) commands.
		 */
		c = gCommands;
		nCmds2Print = 0;
		for (n = 0; n < (int) gNumCommands; c++, n++)
			if ((!iscntrl((int) c->name[0])) && (!(c->flags & kCmdHidden) || showall))
				nCmds2Print++;

		(void) memset((char *) cmdnames, 0, sizeof(cmdnames));

		/* Now form the list we'll be printing, and noting what the maximum
		 * length of a command name was, so we can use that when determining
		 * how to print in columns.
		 */
		c = gCommands;
		i = 0;
		widestName = 0;
		for (n = 0; n < (int) gNumCommands; c++, n++) {
			if ((!iscntrl((int) c->name[0])) && (!(c->flags & kCmdHidden) || showall)) {
				cmdnames[i++] = c->name;
				len = (int) strlen(c->name);
				if (len > widestName)
					widestName = len;
			}
		}

		if ((cp = (char *) getenv("COLUMNS")) == NULL)
			screenColumns = 80;
		else
			screenColumns = atoi(cp);

		/* Leave an extra bit of whitespace for the margins between columns. */
		widestName += 2;

		nCols = (screenColumns + 0) / widestName;
		nRows = nCmds2Print / nCols;
		if ((nCmds2Print % nCols) > 0)
			nRows++;

		for (i = 0; i < nRows; i++) {
			for (j = 0; j < nCols; j++) {
				k = nRows * j + i;
				if (k < nCmds2Print) {
					(void) sprintf(spec, "%%-%ds",
						(j < nCols - 1) ? widestName : widestName - 2
					);
					(void) printf(spec, cmdnames[k]);
				}
			}
			(void) printf("\n");
		}
	} else if (helpall) {
		/* Really intended for me, so I can debug the help strings. */
		for (c = gCommands, n = 0; n < (int) gNumCommands; c++, n++) {
			PrintCmdHelp(c);
			PrintCmdUsage(c);
		}
	} else {
		/* For each command name specified, print its help stuff. */
		for (i=1; i<argc; i++) {
			c = GetCommandByName(argv[i], 0);
			if (c == kAmbiguousCommand) {
				(void) printf("%s: ambiguous command name.\n", argv[i]);
			} else if (c == kNoCommand) {
				(void) printf("%s: no such command.\n", argv[i]);
			} else {
				if (i > 1)
					(void) printf("\n");
				PrintCmdHelp(c);
				PrintCmdUsage(c);
			}
		}
	}
}