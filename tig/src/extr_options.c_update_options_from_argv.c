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
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  commit_order_arg_map ; 
 int /*<<< orphan*/  ignore_space_arg_map ; 
 scalar_t__ map_enum (int*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mark_option_seen (int*) ; 
 int opt_commit_order ; 
 int opt_diff_context ; 
 int opt_ignore_space ; 
 int /*<<< orphan*/  opt_notes_arg ; 
 int opt_show_notes ; 
 scalar_t__ parse_int (int*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
update_options_from_argv(const char *argv[])
{
	int next, flags_pos;

	for (next = flags_pos = 0; argv[next]; next++) {
		const char *flag = argv[next];
		int value = -1;

		if (map_enum(&value, commit_order_arg_map, flag)) {
			opt_commit_order = value;
			mark_option_seen(&opt_commit_order);
			continue;
		}

		if (map_enum(&value, ignore_space_arg_map, flag)) {
			opt_ignore_space = value;
			mark_option_seen(&opt_ignore_space);
			continue;
		}

		if (!strcmp(flag, "--no-notes")) {
			opt_show_notes = false;
			mark_option_seen(&opt_show_notes);
			continue;
		}

		if (!prefixcmp(flag, "--show-notes") ||
		    !prefixcmp(flag, "--notes")) {
			opt_show_notes = true;
			string_ncopy(opt_notes_arg, flag, strlen(flag));
			mark_option_seen(&opt_show_notes);
			continue;
		}

		if (!prefixcmp(flag, "-U")
		    && parse_int(&value, flag + 2, 0, 999999) == SUCCESS) {
			opt_diff_context = value;
			mark_option_seen(&opt_diff_context);
			continue;
		}

		argv[flags_pos++] = flag;
	}

	argv[flags_pos] = NULL;
}