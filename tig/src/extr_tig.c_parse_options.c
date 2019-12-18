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
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {int goto_lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int NCURSES_VERSION ; 
 int /*<<< orphan*/  NCURSES_VERSION_PATCH ; 
 int REQ_VIEW_BLAME ; 
 int REQ_VIEW_DIFF ; 
 int REQ_VIEW_GREP ; 
 int REQ_VIEW_LOG ; 
 int REQ_VIEW_MAIN ; 
 int REQ_VIEW_PAGER ; 
 int REQ_VIEW_REFLOG ; 
 int REQ_VIEW_REFS ; 
 int REQ_VIEW_STASH ; 
 int REQ_VIEW_STATUS ; 
 char* TIG_VERSION ; 
 int /*<<< orphan*/  argv_append (char const***,char const*) ; 
 TYPE_1__ argv_env ; 
 int atoi (char const*) ; 
 scalar_t__ chdir (char const*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_options (char const**,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* rl_library_version ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ string_isnumber (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* usage_string ; 

__attribute__((used)) static enum request
parse_options(int argc, const char *argv[], bool pager_mode)
{
	enum request request;
	const char *subcommand;
	bool seen_dashdash = false;
	bool rev_parse = true;
	const char **filter_argv = NULL;
	int i;

	request = pager_mode ? REQ_VIEW_PAGER : REQ_VIEW_MAIN;

	/* Options that must come before any subcommand. */
	for (i = 1; i < argc; i++) {
		const char *opt = argv[i];
		if (!strncmp(opt, "-C", 2)) {
			if (chdir(opt + 2))
				die("Failed to change directory to %s", opt + 2);
			continue;
		} else {
			break;
		}
	}

	if (i >= argc)
		return request;

	subcommand = argv[i++];
	if (!strcmp(subcommand, "status")) {
		request = REQ_VIEW_STATUS;

	} else if (!strcmp(subcommand, "blame")) {
		request = REQ_VIEW_BLAME;

	} else if (!strcmp(subcommand, "grep")) {
		request = REQ_VIEW_GREP;
		rev_parse = false;

	} else if (!strcmp(subcommand, "show")) {
		request = REQ_VIEW_DIFF;

	} else if (!strcmp(subcommand, "log")) {
		request = REQ_VIEW_LOG;

	} else if (!strcmp(subcommand, "reflog")) {
		request = REQ_VIEW_REFLOG;

	} else if (!strcmp(subcommand, "stash")) {
		request = REQ_VIEW_STASH;

	} else if (!strcmp(subcommand, "refs")) {
		request = REQ_VIEW_REFS;
		rev_parse = false;

	} else {
		subcommand = NULL;
		i--; /* revisit option in loop below */
	}

	for (; i < argc; i++) {
		const char *opt = argv[i];

		// stop parsing our options after -- and let rev-parse handle the rest
		if (!seen_dashdash) {
			if (!strcmp(opt, "--")) {
				seen_dashdash = true;

			} else if (!strcmp(opt, "-v") || !strcmp(opt, "--version")) {
				printf("tig version %s\n", TIG_VERSION);
#ifdef NCURSES_VERSION
				printf("%s version %s.%d\n",
#ifdef NCURSES_WIDECHAR
				       "ncursesw",
#else
				       "ncurses",
#endif
				       NCURSES_VERSION, NCURSES_VERSION_PATCH);
#endif
#ifdef HAVE_READLINE
				printf("readline version %s\n", rl_library_version);
#endif
				exit(EXIT_SUCCESS);

			} else if (!strcmp(opt, "-h") || !strcmp(opt, "--help")) {
				printf("%s\n", usage_string);
				exit(EXIT_SUCCESS);

			} else if (strlen(opt) >= 2 && *opt == '+' && string_isnumber(opt + 1)) {
				int lineno = atoi(opt + 1);

				argv_env.goto_lineno = lineno > 0 ? lineno - 1 : 0;
				continue;

			}
		}

		if (!argv_append(&filter_argv, opt))
			die("command too long");
	}

	if (filter_argv)
		filter_options(filter_argv, rev_parse);

	return request;
}