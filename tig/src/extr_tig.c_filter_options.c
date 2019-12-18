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

/* Variables and functions */
 int /*<<< orphan*/  argv_append (char const***,char const*) ; 
 scalar_t__ argv_parse_rev_flag (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_rev_parse (char const***,char*,char*,char const**) ; 
 char const** opt_cmdline_args ; 
 char const** opt_file_args ; 
 char const** opt_rev_args ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  update_options_from_argv (char const**) ; 

__attribute__((used)) static void
filter_options(const char *argv[], bool rev_parse)
{
	const char **flags = NULL;
	int next, flags_pos;

	update_options_from_argv(argv);

	if (!rev_parse) {
		opt_cmdline_args = argv;
		return;
	}

	/* Add known revision arguments in opt_rev_args and use
	 * git-rev-parse to filter out the remaining options.
	 */
	for (next = flags_pos = 0; argv[next]; next++) {
		const char *arg = argv[next];

		if (!strcmp(arg, "--"))
			while (argv[next])
				argv[flags_pos++] = argv[next++];
		else if (argv_parse_rev_flag(arg, NULL))
			argv_append(&opt_rev_args, arg);
		else
			argv[flags_pos++] = arg;
	}

	argv[flags_pos] = NULL;

	filter_rev_parse(&opt_file_args, "--no-revs", "--no-flags", argv);
	filter_rev_parse(&flags, "--flags", "--no-revs", argv);

	if (flags) {
		for (next = flags_pos = 0; flags && flags[next]; next++) {
			const char *flag = flags[next];

			if (argv_parse_rev_flag(flag, NULL))
				argv_append(&opt_rev_args, flag);
			else
				flags[flags_pos++] = flag;
		}

		flags[flags_pos] = NULL;

		opt_cmdline_args = flags;
	}

	filter_rev_parse(&opt_rev_args, "--symbolic", "--revs-only", argv);
}