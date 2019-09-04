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
struct line_rule {int /*<<< orphan*/  name; int /*<<< orphan*/  member_0; } ;
struct line_info {int attr; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const***) ; 
 int SUCCESS ; 
 struct line_info* add_line_rule (char const*,struct line_rule*) ; 
 int error (char*,...) ; 
 int find_remapped (char const***,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_color_name (char const*,struct line_rule*,char const**) ; 
 int /*<<< orphan*/  set_attribute (int*,char const*) ; 
 int /*<<< orphan*/  set_color (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static enum status_code
option_color_command(int argc, const char *argv[])
{
	struct line_rule rule = {0};
	const char *prefix = NULL;
	struct line_info *info;
	enum status_code code;

	if (argc < 3)
		return error("Invalid color mapping: color area fgcolor bgcolor [attrs]");

	code = parse_color_name(argv[0], &rule, &prefix);
	if (code != SUCCESS)
		return code;

	info = add_line_rule(prefix, &rule);
	if (!info) {
		static const char *obsolete[][2] = {
			{ "acked",			"'    Acked-by'" },
			{ "diff-copy-from",		"'copy from '" },
			{ "diff-copy-to",		"'copy to '" },
			{ "diff-deleted-file-mode",	"'deleted file mode '" },
			{ "diff-dissimilarity",		"'dissimilarity '" },
			{ "diff-rename-from",		"'rename from '" },
			{ "diff-rename-to",		"'rename to '" },
			{ "diff-tree",			"'diff-tree '" },
			{ "filename",			"file" },
			{ "help-keymap",		"help.section" },
			{ "main-revgraph",		"" },
			{ "pp-adate",			"'AuthorDate: '" },
			{ "pp-author",			"'Author: '" },
			{ "pp-cdate",			"'CommitDate: '" },
			{ "pp-commit",			"'Commit: '" },
			{ "pp-date",			"'Date: '" },
			{ "reviewed",			"'    Reviewed-by'" },
			{ "signoff",			"'    Signed-off-by'" },
			{ "stat-head",			"status.header" },
			{ "stat-section",		"status.section" },
			{ "tested",			"'    Tested-by'" },
			{ "tree-dir",			"tree.directory" },
			{ "tree-file",			"tree.file" },
			{ "tree-head",			"tree.header" },
		};
		int index;

		index = find_remapped(obsolete, ARRAY_SIZE(obsolete), rule.name);
		if (index != -1) {
			if (!*obsolete[index][1])
				return error("%s is obsolete", argv[0]);
			/* Keep the initial prefix if defined. */
			code = parse_color_name(obsolete[index][1], &rule, prefix ? NULL : &prefix);
			if (code != SUCCESS)
				return code;
			info = add_line_rule(prefix, &rule);
		}

		if (!info)
			return error("Unknown color name: %s", argv[0]);

		code = error("%s has been replaced by %s",
			     obsolete[index][0], obsolete[index][1]);
	}

	if (!set_color(&info->fg, argv[1]))
		return error("Unknown color: %s", argv[1]);

	if (!set_color(&info->bg, argv[2]))
		return error("Unknown color: %s", argv[2]);

	info->attr = 0;
	while (argc-- > 3) {
		int attr;

		if (!set_attribute(&attr, argv[argc]))
			return error("Unknown color attribute: %s", argv[argc]);
		info->attr |= attr;
	}

	return code;
}