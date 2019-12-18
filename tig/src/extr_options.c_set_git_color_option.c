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
struct line_rule {int /*<<< orphan*/  member_0; } ;
struct line_info {int /*<<< orphan*/  attr; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 struct line_info* add_line_rule (char const*,struct line_rule*) ; 
 char** opt_git_colors ; 
 scalar_t__ parse_color_name (char const*,struct line_rule*,char const**) ; 
 struct line_info* parse_git_color_option (struct line_info*,char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ string_enum_compare (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
set_git_color_option(const char *name, char *value)
{
	struct line_info parsed = {0};
	struct line_info *color = NULL;
	size_t namelen = strlen(name);
	int i;

	if (!opt_git_colors)
		return;

	for (i = 0; opt_git_colors[i]; i++) {
		struct line_rule rule = {0};
		const char *prefix = NULL;
		struct line_info *info;
		const char *alias = opt_git_colors[i];
		const char *sep = strchr(alias, '=');

		if (!sep || namelen != sep - alias ||
		    string_enum_compare(name, alias, namelen))
			continue;

		if (!color) {
			color = parse_git_color_option(&parsed, value);
			if (!color)
				return;
		}

		if (parse_color_name(sep + 1, &rule, &prefix) == SUCCESS &&
		    (info = add_line_rule(prefix, &rule))) {
			info->fg = parsed.fg;
			info->bg = parsed.bg;
			info->attr = parsed.attr;
		}
	}
}