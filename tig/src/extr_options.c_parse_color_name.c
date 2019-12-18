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
struct line_rule {char const* line; char const* name; void* namelen; void* linelen; } ;
struct keymap {char* name; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int SUCCESS ; 
 int error (char*,int,char const*) ; 
 struct keymap* get_keymap (char const*,int) ; 
 scalar_t__ is_quoted (char const) ; 
 int /*<<< orphan*/  memset (struct line_rule*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 void* strlen (char const*) ; 

__attribute__((used)) static enum status_code
parse_color_name(const char *color, struct line_rule *rule, const char **prefix_ptr)
{
	const char *prefixend = is_quoted(*color) ? NULL : strchr(color, '.');

	if (prefixend) {
		struct keymap *keymap = get_keymap(color, prefixend - color);

		if (!keymap)
			return error("Unknown key map: %.*s", (int) (prefixend - color), color);
		if (prefix_ptr)
			*prefix_ptr = keymap->name;
		color = prefixend + 1;
	}

	memset(rule, 0, sizeof(*rule));
	if (is_quoted(*color)) {
		rule->line = color + 1;
		rule->linelen = strlen(color) - 2;
	} else {
		rule->name = color;
		rule->namelen = strlen(color);
	}

	return SUCCESS;
}