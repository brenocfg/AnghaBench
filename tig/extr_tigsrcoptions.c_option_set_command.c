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
struct option_info {int dummy; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const***) ; 
 int SUCCESS ; 
 int error (char*,...) ; 
 struct option_info* find_option_info (char const***,int /*<<< orphan*/ ,char*,char const*) ; 
 int find_remapped (char const***,int /*<<< orphan*/ ,char const*) ; 
 char const*** option_info ; 
 int option_update (struct option_info*,int,char const**) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static enum status_code
option_set_command(int argc, const char *argv[])
{
	struct option_info *option;

	if (argc < 2)
		return error("Invalid set command: set option = value");

	if (strcmp(argv[1], "="))
		return error("No value assigned to %s", argv[0]);

	option = find_option_info(option_info, ARRAY_SIZE(option_info), "", argv[0]);
	if (option)
		return option_update(option, argc, argv);

	{
		const char *obsolete[][2] = {
			{ "status-untracked-dirs", "status-show-untracked-dirs" },
		};
		int index = find_remapped(obsolete, ARRAY_SIZE(obsolete), argv[0]);

		if (index != -1) {
			option = find_option_info(option_info, ARRAY_SIZE(option_info), "", obsolete[index][1]);
			if (option) {
				enum status_code code = option_update(option, argc, argv);

				if (code != SUCCESS)
					return code;
				return error("%s has been renamed to %s",
					     obsolete[index][0], obsolete[index][1]);
			}
		}
	}

	{
		const char *obsolete[][2] = {
			{ "author-width",		"author" },
			{ "filename-width",		"file-name" },
			{ "line-number-interval",	"line-number" },
			{ "show-author",		"author" },
			{ "show-date",			"date" },
			{ "show-file-size",		"file-size" },
			{ "show-filename",		"file-name" },
			{ "show-id",			"id" },
			{ "show-line-numbers",		"line-number" },
			{ "show-refs",			"commit-title" },
			{ "show-rev-graph",		"commit-title" },
			{ "title-overflow",		"commit-title and text" },
		};
		int index = find_remapped(obsolete, ARRAY_SIZE(obsolete), argv[0]);

		if (index != -1)
			return error("%s is obsolete; see tigrc(5) for how to set the %s column option",
				     obsolete[index][0], obsolete[index][1]);

		if (!strcmp(argv[0], "read-git-colors"))
			return error("read-git-colors has been obsoleted by the git-colors option");

		if (!strcmp(argv[0], "cmdline-args"))
			return error("cmdline-args is obsolete; use view-specific options instead, e.g. main-options");
	}

	return error("Unknown option name: %s", argv[0]);
}