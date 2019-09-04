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
struct line_info {char* prefix; int /*<<< orphan*/  attr; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; struct line_info* next; } ;
struct line_rule {char* line; int /*<<< orphan*/  name; struct line_info info; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_fprintf (int /*<<< orphan*/ *,char*,char const*,char const*,char const*,char const*,char const*,int,char*) ; 
 int /*<<< orphan*/  save_option_color_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_option_color_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool
save_option_color(void *data, const struct line_rule *rule)
{
	FILE *file = data;
	const struct line_info *info;

	for (info = &rule->info; info; info = info->next) {
		const char *prefix = info->prefix ? info->prefix : "";
		const char *prefix_sep = info->prefix ? "." : "";
		const char *quote = *rule->line ? "\"" : "";
		const char *name = *rule->line ? rule->line : enum_name(rule->name);
		int name_width = strlen(prefix) + strlen(prefix_sep) + 2 * strlen(quote) + strlen(name);
		int padding = name_width > 30 ? 0 : 30 - name_width;

		if (!io_fprintf(file, "\ncolor %s%s%s%s%s%-*s",
				      prefix, prefix_sep, quote, name, quote, padding, "")
		    || !save_option_color_name(file, info->fg)
		    || !save_option_color_name(file, info->bg)
		    || !save_option_color_attr(file, info->attr))
			return false;
	}

	return true;
}